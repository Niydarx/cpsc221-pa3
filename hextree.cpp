/**
 * @file hextree.cpp
 * @description student implementation of HexTree class used for storing image data
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE
 */

#include "hextree.h"
#include <queue>
#include <stack>




/**
 * Constructor that builds a HexTree out of the given PNG.
 * Every leaf in the tree corresponds to a pixel in the PNG.
 * Every non-leaf node corresponds to a rectangle of pixels
 * in the original PNG, represented by an (x,y) pair for the
 * upper left corner of the rectangle and an (x,y) pair for
 * lower right corner of the rectangle. In addition, the Node
 * stores a RGBAPixel representing the average colour over the
 * rectangle.
 *
 * The average colour for each node in your implementation MUST
 * be determined in constant time. HINT: this will lead to nodes
 * at shallower levels of the tree accumulating some error in their
 * average colour value, but we will accept this consequence in
 * exchange for faster tree construction.
 * Note that we will be looking for specific colour values in our
 * autograder, so if you instead perform a slow but accurate
 * average colour computation, you will likely fail the test cases!
 *
 * Every node's children correspond to a partition of the
 * node's rectangle into (up to) six smaller rectangles. The node's
 * rectangle is split evenly (or as close to evenly as possible)
 * along both horizontal and vertical axes. If an even split along
 * the vertical axis is not possible, the extra line(s) will be included
 * in either the middle section, or distributed to the left and right sections;
 * If an even split along the horizontal axis is not
 * possible, the extra line will be included in the upper side.
 * If a single-pixel-wide rectangle needs to be split, the left and right children
 * will be null.
 * If a single-pixel-tall rectangle needs to be split,
 * the lower children will be null.
 *
 * In this way, each of the children's rectangles together will have coordinates
 * that when combined, completely cover the original rectangle's image
 * region and do not overlap.
 */
HexTree::HexTree(const PNG &imIn)
{
    _imageWidth = imIn.width();
    _imageHeight = imIn.height();
    /**
     * Using SummedAreaTable
     * summedAreaTable.resize(imageWidth, vector<RGBSum>(imageHeight));
     * createSummedAreaTable(imageWidth, imageHeight, imIn);
     */

    // Init root node. Root represents the entire image
    // Call BuildNode to recursively build out the tree
    root = BuildNode(imIn, {0, 0}, {_imageWidth - 1, _imageHeight - 1});
}

/**
 * Overloaded assignment operator for HexTree.
 * Part of the Big Three that we must define because the class
 * allocates dynamic memory. This depends on your implementation
 * of the copy and clear funtions.
 * You may refer to the assignment operator defined and given in PA1.
 * Make sure you understand what its implementation means.
 *
 * @param rhs The right hand side of the assignment statement.
 */
HexTree &HexTree::operator=(const HexTree &rhs)
{
    // Replace the line below with your implementation
    return *this;
}

/**
 * Render returns a PNG image consisting of the pixels
 * stored in the tree. May be used on pruned trees. Draws
 * every leaf node's rectangle onto a PNG canvas using the
 * average colour stored in the node.
 *
 * @param fulldepth whether to render each path fully to a leaf node,
 *                  or to only render down to maxlevel
 * @param maxlevel the maximum depth to render in the tree (ignored if fulldepth == true)
 *                 Beware that maxlevel might be larger than
 *                 the length of some paths in pruned trees
 */
PNG HexTree::Render(bool fulldepth, unsigned int maxlevel) const
{
    PNG returnPNG(_imageWidth, _imageHeight);
    Render(returnPNG, root, fulldepth, maxlevel);
    return returnPNG;
}

/**
 *  Prune function trims subtrees as high as possible in the tree.
 *  A subtree is pruned (cleared) if all of the subtree's leaves are within
 *  tolerance of the average colour stored in the root of the subtree.
 *  NOTE - you may use the distanceTo function found in RGBAPixel.h
 *  Pruning criteria should be evaluated on the original tree, not
 *  on any pruned subtree. (we only expect that trees would be pruned once.)
 *
 * You may want at least one recursive helper function for this one.
 *
 * @param tolerance maximum RGBA distance to qualify for pruning
 * @pre this tree has not previously been pruned, nor is copied from a previously pruned tree.
 */
void HexTree::Prune(double tolerance)
{
   pruneNode(root, tolerance);
}

/**
 *  FlipHorizontal rearranges the contents of the tree, so that
 *  its rendered image will appear mirrored across a vertical axis.
 *  This may be called on a previously pruned/flipped/rotated tree.
 *
 *  After flipping, the A/B/C/D/E/F pointers must map to what will be
 *  physically rendered in the respective NW/NE/SW/SE regions.
 *
 *  You may want a recursive helper function for this one.
 */
void HexTree::FlipHorizontal()
{
    // ADD YOUR IMPLEMENTATION BELOW
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current HexTree object. Complete for PA3.
 * You may want a recursive helper function for this one.
 */
void HexTree::Clear()
{
    Clear(root);

    root = nullptr;
}

/**
 * Copies the parameter other HexTree into the current HexTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other The HexTree to be copied.
 */
void HexTree::Copy(const HexTree &other)
{
    // ADD YOUR IMPLEMENTATION BELOW
}

/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param img reference to the original input image.
 * @param ul upper left point of current node's rectangle.
 * @param lr lower right point of current node's rectangle.
 */
Node *HexTree::BuildNode(const PNG &img, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{
    unsigned int nodeWidth = (lr.first - ul.first) + 1;
    unsigned int nodeHeight = (lr.second - ul.second) + 1;
    if (ul == lr)
    {
        /**
         * SummedAreaTable implementation
          RGBSum curPixelSum = pixelToSum(*img.getPixel(ul.first, ul.second));
          int x = ul.first;
          int y = ul.second;
          if (x > 0 && y > 0)
          {
              RGBSum columnArea = summedAreaTable[x][y - 1];
              RGBSum rowArea = summedAreaTable[x - 1][y];
              RGBSum diagArea = summedAreaTable[x - 1][y - 1];
              RGBSum curArea = subtractRGBASums(addRGBASums(addRGBASums(curPixelSum, rowArea), columnArea), diagArea);
              summedAreaTable[x][y] = curArea;
          }
          else if (x > 0)
          {
              RGBSum rowArea = summedAreaTable[x - 1][y];
              summedAreaTable[x][0] = addRGBASums(curPixelSum, rowArea);
          }
          else if (y > 0)
          {
              RGBSum columnArea = summedAreaTable[x][y - 1];
              summedAreaTable[0][y] = addRGBASums(curPixelSum, columnArea);
          }
          else
          {
              summedAreaTable[x][y] = curPixelSum;
          }
          summedAreaTable[ul.first][ul.second] = pixelToSum(*img.getPixel(ul.first, ul.second));
         */

        Node *baseNode = new Node(ul, lr, *img.getPixel(ul.first, ul.second));
        return baseNode;
    }
    else
    {
        unsigned int leftW = nodeWidth / 3;   // integer division
        unsigned int midW = nodeWidth / 3;    // integer division
        unsigned int rightW = nodeWidth / 3;  // integer division
        unsigned int upperH = nodeHeight / 2; // integer division
        unsigned int lowerH = nodeHeight / 2; // integer division
        bool skipSides = (nodeWidth == 1);    // node is a single col
        bool skipMid = (nodeWidth == 2);      // node has width == 2
        bool skipBottom = (nodeHeight == 1);  // node is a single row

        Node *A = nullptr;
        Node *B = nullptr;
        Node *C = nullptr;
        Node *D = nullptr;
        Node *E = nullptr;
        Node *F = nullptr;

        pair<unsigned int, unsigned int> subUpperLeft;
        pair<unsigned int, unsigned int> subLowerRight;

        // distribute extra pixels
        if (nodeHeight % 2 == 1)
        {
            upperH++;
        }
        if (nodeWidth % 3 == 1)
        {
            midW++;
        }
        else if (nodeWidth % 3 == 2)
        {
            leftW++;
            rightW++;
        }
        if (!skipSides)
        {
            // Node A
            subUpperLeft = {ul.first, ul.second};
            subLowerRight = {max(ul.first + leftW - 1, ul.first), max(ul.second + upperH - 1, ul.second)};
            A = BuildNode(img, subUpperLeft, subLowerRight);
            // Node C
            subUpperLeft = {ul.first + leftW + midW, ul.second};
            subLowerRight = {max(ul.first + leftW + midW + rightW - 1, ul.first + leftW + midW), max(ul.second + upperH - 1, ul.second)};
            C = BuildNode(img, subUpperLeft, subLowerRight);
        }

        if (!skipMid)
        {
            // Node B
            subUpperLeft = {ul.first + leftW, ul.second};
            subLowerRight = {max(ul.first + leftW + midW - 1, ul.first + leftW), max(ul.second + upperH - 1, ul.second)};
            B = BuildNode(img, subUpperLeft, subLowerRight);
        }

        if (!skipBottom)
        {
            if (!skipSides)
            {
                // Node D
                subUpperLeft = {ul.first, ul.second + upperH};
                subLowerRight = {max(ul.first + leftW - 1, ul.first), max(lr.second, ul.second + upperH)};
                D = BuildNode(img, subUpperLeft, subLowerRight);
                // Node F
                subUpperLeft = {ul.first + leftW + midW, ul.second + upperH};
                subLowerRight = {max(ul.first + leftW + midW + rightW - 1, ul.first + leftW + midW), max(lr.second, ul.second + upperH)};
                F = BuildNode(img, subUpperLeft, subLowerRight);
            }
            if (!skipMid)
            {
                // Node E
                subUpperLeft = {ul.first + leftW, ul.second + upperH};
                subLowerRight = {max(ul.first + leftW + midW - 1, ul.first + leftW), max(lr.second, ul.second + upperH)};
                E = BuildNode(img, subUpperLeft, subLowerRight);
            }
        }
        // Node *returnNode = new Node(ul, lr, calculateAverage(ul, lr));
        Node *returnNode = new Node(ul, lr, averageFromChildren(A, B, C, D, E, F, ul, lr));
        returnNode->A = A; // upper-left child
        returnNode->B = B; // upper-middle child
        returnNode->C = C; // upper-right child
        returnNode->D = D; // lower-left child
        returnNode->E = E; // lower-middle child
        returnNode->F = F; // lower-right child
        return returnNode;
    }
}

/*********************************************************/
/*** IMPLEMENT YOUR OWN PRIVATE MEMBER FUNCTIONS BELOW ***/
/*********************************************************/

/**
 * Returns an RGBSum with the sums the values of two given RGBSums
 * @param a An RGBSum
 * @param b An RGBSum
 */
HexTree::RGBSum HexTree::addRGBASums(RGBSum a, RGBSum b)
{
    HexTree::RGBSum retSum;
    retSum.r = a.r + b.r;
    retSum.g = a.g + b.g;
    retSum.b = a.b + b.b;
    return retSum;
}

/**
 * Returns an RGBSum with the difference the values of two given RGBSums
 * @pre a > b
 * @param a An RGBSum
 * @param b RGBSum to subtract from a
 */
HexTree::RGBSum HexTree::subtractRGBASums(RGBSum a, RGBSum b)
{
    HexTree::RGBSum retSum;
    retSum.r = a.r - b.r;
    retSum.g = a.g - b.g;
    retSum.b = a.b - b.b;
    return retSum;
}

// Returns an RGBSum given an RGBAPixel
HexTree::RGBSum HexTree::pixelToSum(const RGBAPixel p)
{
    HexTree::RGBSum retSum;
    retSum.r = p.r;
    retSum.g = p.g;
    retSum.b = p.b;
    return retSum;
}

/**
 * Summed Area Table implementation.
void HexTree::createSummedAreaTable(unsigned int imageWidth, unsigned int imageHeight, const PNG &imIn)
{
    for (unsigned int x = 0; x < imageWidth; x++)
    {
        for (unsigned int y = 0; y < imageHeight; y++)
        {
            RGBAPixel *curPixel = imIn.getPixel(x, y);
            RGBSum curPixelSum = pixelToSum(*curPixel);
            if (x > 0 && y > 0)
            {
                RGBSum columnArea = summedAreaTable[x][y - 1];
                RGBSum rowArea = summedAreaTable[x - 1][y];
                RGBSum diagArea = summedAreaTable[x - 1][y - 1];
                RGBSum curArea = subtractRGBASums(addRGBASums(addRGBASums(curPixelSum, rowArea), columnArea), diagArea);
                summedAreaTable[x][y] = curArea;
            }
            else if (x > 0)
            {
                RGBSum rowArea = summedAreaTable[x - 1][y];
                summedAreaTable[x][0] = addRGBASums(curPixelSum, rowArea);
            }
            else if (y > 0)
            {
                RGBSum columnArea = summedAreaTable[x][y - 1];
                summedAreaTable[0][y] = addRGBASums(curPixelSum, columnArea);
            }
            else
            {
                summedAreaTable[x][y] = curPixelSum;
            }
        }
    }
}


RGBAPixel HexTree::calculateAverage(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{

    unsigned int x1 = ul.first;
    unsigned int x2 = lr.first;
    unsigned int y1 = ul.second;
    unsigned int y2 = lr.second;

    RGBSum total = summedAreaTable[x2][y2];
    if (x1 > 0)
    {
        total = subtractRGBASums(total, summedAreaTable[x1 - 1][y2]);
    }
    if (y1 > 0)
    {
        total = subtractRGBASums(total, summedAreaTable[x2][y1 - 1]);
    }
    if (x1 > 0 && y1 > 0)
    {
        total = addRGBASums(total, summedAreaTable[x1 - 1][y1 - 1]);
    }
    int numPixels = (x2 - x1 + 1) * (y2 - y1 + 1);

    RGBAPixel returnPixel(returnPixel.r = total.r / (long)numPixels,
                          returnPixel.g = total.g / (long)numPixels,
                          returnPixel.b = total.b / (long)numPixels);

    return returnPixel;
}
*/

RGBAPixel HexTree::averageFromChildren(Node *A, Node *B, Node *C, Node *D, Node *E, Node *F, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{
    unsigned int x1 = ul.first;
    unsigned int x2 = lr.first;
    unsigned int y1 = ul.second;
    unsigned int y2 = lr.second;
    int numPixels = (x2 - x1 + 1) * (y2 - y1 + 1);
    int totalR = 0;
    int totalG = 0;
    int totalB = 0;
    if (A != nullptr)
    {
        int areaA = (A->lowRight.first - A->upLeft.first + 1) * (A->lowRight.second - A->upLeft.second + 1);
        totalR += A->avg.r * areaA;
        totalG += A->avg.g * areaA;
        totalB += A->avg.b * areaA;
    }
    if (B != nullptr)
    {
        int areaB = (B->lowRight.first - B->upLeft.first + 1) * (B->lowRight.second - B->upLeft.second + 1);
        totalR += B->avg.r * areaB;
        totalG += B->avg.g * areaB;
        totalB += B->avg.b * areaB;
    }
    if (C != nullptr)
    {
        int areaC = (C->lowRight.first - C->upLeft.first + 1) * (C->lowRight.second - C->upLeft.second + 1);
        totalR += C->avg.r * areaC;
        totalG += C->avg.g * areaC;
        totalB += C->avg.b * areaC;
    }
    if (D != nullptr)
    {
        int areaD = (D->lowRight.first - D->upLeft.first + 1) * (D->lowRight.second - D->upLeft.second + 1);
        totalR += D->avg.r * areaD;
        totalG += D->avg.g * areaD;
        totalB += D->avg.b * areaD;
    }
    if (E != nullptr)
    {
        int areaE = (E->lowRight.first - E->upLeft.first + 1) * (E->lowRight.second - E->upLeft.second + 1);
        totalR += E->avg.r * areaE;
        totalG += E->avg.g * areaE;
        totalB += E->avg.b * areaE;
    }
    if (F != nullptr)
    {
        int areaF = (F->lowRight.first - F->upLeft.first + 1) * (F->lowRight.second - F->upLeft.second + 1);
        totalR += F->avg.r * areaF;
        totalG += F->avg.g * areaF;
        totalB += F->avg.b * areaF;
    }
    return RGBAPixel(totalR / numPixels, totalG / numPixels, totalB / numPixels);
}

void HexTree::Render(PNG &img, const Node *nd, bool fulldepth, unsigned int maxlevel) const
{
    if (nd != nullptr)
    {
        if ((!fulldepth && maxlevel == 0) || isLeafNode(nd))
        {
            pair<unsigned int, unsigned int> ul = nd->upLeft;
            pair<unsigned int, unsigned int> lr = nd->lowRight;
            unsigned int nodeWidth = (lr.first - ul.first) + 1;
            unsigned int nodeHeight = (lr.second - ul.second) + 1;
            unsigned int x = ul.first;
            unsigned int y = ul.second;
            for (unsigned int plotX = 0; plotX < nodeWidth; plotX++)
            {
                for (unsigned int plotY = 0; plotY < nodeHeight; plotY++)
                {
                    RGBAPixel *curOutPixel = img.getPixel(x + plotX, y + plotY);
                    *curOutPixel = nd->avg;
                }
            }
        }
        else
        {
            if (!fulldepth)
            {
                maxlevel--;
            }
            Render(img, nd->A, fulldepth, maxlevel);
            Render(img, nd->B, fulldepth, maxlevel);
            Render(img, nd->C, fulldepth, maxlevel);
            Render(img, nd->D, fulldepth, maxlevel);
            Render(img, nd->E, fulldepth, maxlevel);
            Render(img, nd->F, fulldepth, maxlevel);
        }
    }
}

void HexTree::Clear(Node*& nd)
{
    /*
    if (nd != nullptr)
    {
        if (isLeafNode(nd))
        {
            if (nd == root)
            {
                delete root;
                root = nullptr;
            }
            else
            {
                delete nd;
            }
            nd = nullptr;
        }
        else
        {
            // Node A
            if (nd->A != nullptr && isLeafNode(nd->A))
            {
                delete nd->A;
                nd->A = nullptr;
            }
            else
            {
                Clear(nd->A);
            }

            // Node B
            if (nd->B != nullptr && isLeafNode(nd->B))
            {
                delete nd->B;
                nd->B = nullptr;
            }
            else
            {
                Clear(nd->B);
            }

            // Node C
            if (nd->C != nullptr && isLeafNode(nd->C))
            {
                delete nd->C;
                nd->C = nullptr;
            }
            else
            {
                Clear(nd->C);
            }

            // Node D
            if (nd->D != nullptr && isLeafNode(nd->D))
            {
                delete nd->D;
                nd->D = nullptr;
            }
            else
            {
                Clear(nd->D);
            }

            // Node E
            if (nd->E != nullptr && isLeafNode(nd->E))
            {
                delete nd->E;
                nd->E = nullptr;
            }
            else
            {
                Clear(nd->E);
            }

            // Node F
            if (nd->F != nullptr && isLeafNode(nd->F))
            {
                delete nd->F;
                nd->F = nullptr;
            }
            else
            {
                Clear(nd->F);
            }
            delete nd;
            nd = nullptr;
        }
    }
    */

   //base case: node is null

    if (nd == nullptr) {
        return;
    } 

    //recursive call: delete all the subtrees below this node first.
    Clear(nd->A);
    Clear(nd->B);
    Clear(nd->C);
    Clear(nd->D);
    Clear(nd->E);
    Clear(nd->F);

    //work on current recursion level: delete the current node
    delete nd;
    nd = nullptr;
}

bool HexTree::isLeafNode(const Node *nd) const
{
    return (nd->A == nullptr && nd->B == nullptr && nd->C == nullptr && nd->D == nullptr && nd->E == nullptr && nd->F == nullptr);
}

/**
 * Recursive helper for Prune. Pushes highest prunable subtrees of nd to the stack                                                                               
 * @pre An unpruned subtree
 * @param nd the root node of a subtree
 * @param tolerance the tolerance for whether or not to prune the subtree.
 * @return -1 if subtree doesn't exist, 0 if subtree is not prunable, and 1 if subtree is prunable                                                        e
 */

/*
int getPrunableSubtrees(Node* nd, double tolerance, std::stack<Node*>* st) const
{
    //prunable is a flag that checks whether or not every leaf of a subtree is within tolerance
    int prunable = 1;

    //numleaves is the sum of non null children
    int numChild = 0;

    //temp var for current nd's children prunable value
    //case 1: childPrunable is 1, so child is prunable
        //prunable remains positive
        //numchild is incremented by 1
    //case 2: childPrunable is 0, so child is not prunable
        //prunable * 0 is 0, so current node is not prunable
        //numChild in this case doesnt matter, so is unchanged
    //case 3: childPrunableis -1, so child doesn't exist
        //doesn' affect prunable, since a node can still be prunable with less nodes
        //numChild is unchanged
    Node* currChild;
    int childPrunable;

    //temp queue to iterate thru children
    std::queue<Node*>* q;

    //base case: nd is a leaf, so by default is prunable

    if (isLeafNode(nd)) {
        st->push(nd);
        return 1;
    }

    //base case: nd does not exist.
    if (nd == nullptr) {
        return -1;
    }

    q->push(nd->A);
    q->push(nd->B);
    q->push(nd->C);
    q->push(nd->D);
    q->push(nd->E);
    q->push(nd->F);

    //otherwise, recursively check every subtree under nd. 

    //case 1: childPrunable is 1, so child is prunable
        //prunable remains positive
        //numchild is incremented by 1
    //case 2: childPrunable is 0, so child is not prunable
        //prunable * 0 is 0, so current node is not prunable, and exit the loop
        //numChild in this case doesnt matter, so is unchanged
    //case 3: childPrunableis -1, so child doesn't exist
        //doesn' affect prunable, since a node can still be prunable with less nodes
        //numChild is unchanged
    while  (!q->empty()) {
        currChild = q->front();
        q->pop();
        childPrunable = getPrunableSubtrees(nd->A, tolerance, st);
        if (childPrunable >= 1) {
            numChild++;

        } else if(childPrunable == 0) {
            prunable = -1;
            break;
        } //else temp is 0 so numChild doesnt change and prunable doesnt change
    }

    //if prunable is positive, calculate the tolerance within the current png block
    if (prunable >= 1) {
        for (int temp = numChild; temp > 0; temp--) {
            st->pop();
        }
        st->push(nd);
    } 

    //if prunable is negative, the block is not going to be prunable, and the parent of this is definitely not gonna be prunable

    return prunable;
}
*/

void HexTree::pruneNode(Node*& nd, double tolerance)
{
    //base case: nd is null
    if (nd == nullptr) {
        return;
    }

      // First check if we should prune this entire subtree
    if (shouldPrune(nd, tolerance, nd->avg)) {
        Clear(nd->A);  // Recursively deletes all children
        Clear(nd->B);
        Clear(nd->C);
        Clear(nd->D);
        Clear(nd->E);
        Clear(nd->F);
        return;
    }

    pruneNode(nd->A, tolerance);
    pruneNode(nd->B, tolerance);
    pruneNode(nd->C, tolerance);
    pruneNode(nd->D, tolerance);
    pruneNode(nd->E, tolerance);
    pruneNode(nd->F, tolerance);


    
}

bool HexTree::shouldPrune(Node* nd, double tolerance, RGBAPixel& avg) const {
    
    //base case: nd is null, so is trivially in tolerance
    if (nd == nullptr) {
        return true;
    }

    //base case: at a leaf node, so check whether avg is within tolerance
    if (isLeafNode(nd)) {
        return nd->avg.distanceTo(avg) <= tolerance;
    }
    
    //otherwise, recursively travel down

    return shouldPrune(nd->A, tolerance, avg) 
            && shouldPrune(nd->B, tolerance, avg) 
            && shouldPrune(nd->C, tolerance, avg) 
            && shouldPrune(nd->D, tolerance, avg) 
            && shouldPrune(nd->E, tolerance, avg) 
            && shouldPrune(nd->F, tolerance, avg);
}

