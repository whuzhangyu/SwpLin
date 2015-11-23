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
    EQ = Heapify(all segment endpoints);

    // initialize sweep line data structure SL to be empty
    // SL is stored using a binary search tree class
    SL = new class BST(Null);

    // initialize the output intersection array list IL to be empty
    IL = new class List(Null);

    while (EQ != Null)
    {
        // pop up the root of the EQ to get the next event
        // that's the left-most event point
        E = EQ.PopRoot();

        // if E is the left endpoint of segment
        if (IsLeftEndPoint(E) == true)
        {
            // get the segment of E
            segE = FindSegID(E);
            // add segment segE to the sweep line SL
            SL.Insert(segE);
            // find the segment above segE in SL, that is the
            // in-order predecessor of segE in SL
            segA = SL.FindInOrderPre(segE);
            // find the segment below segE in SL, that is the
            // in-order successor of segE in SL
            segB = SL.FindInOrderAfter(segE);
            // detect if segE and segA are intersected
            if ((I = Intersection(segE, segA)) != Null)
            {
                // if intersected, add the intersection into EQ
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
            segA = SL.FindInOrderPre(segE);
            // find the segment below segE in SL
            segB = SL.FindInOrderAfter(segE);
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
                    // add the intersection into EQ
                    EQ.Push(I);
                }
            }
        }
        // if E is an intersection event
        else
        {
            // add E into the output list IL
            IL.Add(E);
            // get the upper segment of intersection I
            segE1 = SL.FindInOrderPre(I);
            // get the lower segment of intersection I
            segE2 = SL.FindInOrderAfter(I);
            // swap their positions so that segE2 is above segE1
            SL.Swaposition(segE1, segE2);
            // get the segment above segE2 in SL
            segA = SL.FindInOrderPre(segE2);
            // get the segment below segE1 in SL
            segB = SL.FindInOrderAfter(segE1);
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