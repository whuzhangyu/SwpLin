// BOA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
    return 0;
}

// segments intersections detection
// sweepline algorithm implemented
Sweepline Algorithm
{
    // initialize event data structure - minimum priority queue
    // event queue EQ initially stores all the start and end points
    // of all the input line segments, and the endpoints are stored in the
    // minimum priority queue according to their x coordinates
    // each node of EQ is a data structure consists of the coordinates of
    // the point, and two IDs (seg1, seg2) of the two segments which
    // intersect at the point, if the point is not an intersection point,
    // then it only stores the ID of the segment which it belongs to
    EQ = Heapify(all segment endpoints);

    // initialize sweep line data structure SL to be empty
    // SL is a binary search tree class, stores the active segments
    // according to the y coordinates of their intersections with the
    // sweep line
    SL = new class BST(Null);

    // initialize the output intersection array list IL to be empty
    IL = new class List(Null);

    while (EQ != Null)
    {
        // pop up the root of the EQ to get the next event
        // that's the left-most event point, this means the sweep line
        // moves from left to right
        E = EQ.PopRoot();

        // if E is the left endpoint of segment
        if (IsLeftEndPoint(E) == true)
        {
            // get the segment of E
            segE = FindSegID(E);
            // add segment segE to the sweep line SL
            SL.Insert(segE);
            // find the segment above segE in SL, that is the
            // in-order successor of segE in SL
            segA = SL.FindInOrderNext(segE);
            // find the segment below segE in SL, that is the
            // in-order predecessor of segE in SL
            segB = SL.FindInOrderPre(segE);
            // detect if segE and segA are intersected
            if ((I = Intersection(segE, segA)) != Null)
            {
                // if intersected, add the intersection I into EQ
                EQ.Push(I);
            }
            // detect if segE and segB are intersected
            if ((I = Intersection(segE, segB)) != Null)
            {
                // if intersected, add the intersection into EQ
                EQ.Push(I);
            }
        }
        // if E is the right endpoint of segment
        else if (IsRightEndPoint(E) == true)
        {
            // get the segment of E
            segE = FindSegID(E);
            // find the segment above segE in SL
            segA = SL.FindInOrderNext(segE);
            // find the segment below segE in SL
            segB = SL.FindInOrderPre(segE);
            // delete segE from SL
            SL.Remove(segE);
            // now segA and segB are neighbours
            // detect if segA and segB are intersected
            if ((I = Intersection(segA, segB)) != Null)
            {
                // if segA and segB are intersected, and 
                // the intersection I is not in EQ already
                if (EQ.Find(I) == null)
                {
                    // add the intersection I into EQ
                    EQ.Push(I);
                }
            }
        }
        // if E is an intersection event
        else
        {
            // add E into the output list IL
            IL.Add(E);
            // get the upper segment among the two segments that intersect
            // at E, that's the right one in the in-order traversal of SL
            segE1 = SL.InOrderRightOne(E.seg1, E.seg2);
            // get the lower segment of intersection I
            segE2 = SL.InOrderLeftOne(E.seg1, E.seg2);
            // swap their positions so that segE2 is above segE1
            SL.Swaposition(segE1, segE2);
            // get the segment above segE2 in SL
            segA = SL.FindInOrderNext(segE2);
            // get the segment below segE1 in SL
            segB = SL.FindInOrderPre(segE1);
            // now segA and segE2 are neighbours
            // detect if segA and segE2 are intersected
            if ((I = Intersection(segA, segE2)) != Null)
            {
                // if segA and segE2 are intersected, and 
                // the intersection I is not in EQ already
                if (EQ.Find(I) == null)
                {
                    // add the intersection into EQ
                    EQ.Push(I);
                }
            }
            // now segB and segE1 are neighbours
            // detect if segB and segE1 are intersected
            if ((I = Intersection(segB, segE1)) != Null)
            {
                // if segB and segE1 are intersected, and 
                // the intersection I is not in EQ already
                if (EQ.Find(I) == Null)
                {
                    // add the intersection into EQ
                    EQ.Push(I);
                }
            }
        }
        // now event E is processed, continue to the next event
    }
    // now all the events are processed,
    // return the intersection list IL
    return IL;
}