/**
 * @file hextree.cpp
 * @description student implementation of HexTree class used for storing image data
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE
 */

#include "hextree.h"

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
HexTree::HexTree(const PNG& imIn) {
	// ADD YOUR IMPLEMENTATION BELOW

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
HexTree& HexTree::operator=(const HexTree& rhs) {
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
PNG HexTree::Render(bool fulldepth, unsigned int maxlevel) const {
	// Replace the line below with your implementation
	return PNG();
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
void HexTree::Prune(double tolerance) {
	// ADD YOUR IMPLEMENTATION BELOW

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
void HexTree::FlipHorizontal() {
	// ADD YOUR IMPLEMENTATION BELOW

}

/**
 * Destroys all dynamically allocated memory associated with the
 * current HexTree object. Complete for PA3.
 * You may want a recursive helper function for this one.
 */
void HexTree::Clear() {
	// ADD YOUR IMPLEMENTATION BELOW

}

/**
 * Copies the parameter other HexTree into the current HexTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other The HexTree to be copied.
 */
void HexTree::Copy(const HexTree& other) {
	// ADD YOUR IMPLEMENTATION BELOW

}

/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param img reference to the original input image.
 * @param ul upper left point of current node's rectangle.
 * @param lr lower right point of current node's rectangle.
 */
Node* HexTree::BuildNode(const PNG& img, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr) {
	// Replace the line below with your implementation
	return nullptr;
}

/*********************************************************/
/*** IMPLEMENT YOUR OWN PRIVATE MEMBER FUNCTIONS BELOW ***/
/*********************************************************/

