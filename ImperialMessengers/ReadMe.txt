========================================================================
    CONSOLE APPLICATION : ImperialMessengers Project Overview
========================================================================

This is a simple app once I did the cleanup. The hardest part is the text reading algorithm
which has a lot of error checking and had to go through extensive testing, which I am
sure that I still missed a few bugs (you always do).

The algorithm is a simple dyksra and tracks the shortest distance from the origin, node 0,
in a simple array and then looks for shorter ways to get there. Typical for Dykstra,
it's a combination of breadth-first and depth-first search.

The algorithm does some setup in "StartWalk" and does the search in "WalkToNextTowns".

Total time including false starts, testing, and cleanup was around 6 hours. I also
did a lot of thinking before even starting.

/////////////////////////////////////////////////////////////////////////////
alternate methods tried:

I started with A* (I wrote a book on this topic) but I soon realized that this would not allow 
for multiple cities to be considered as good destinations from a single city.

As a second attemp, I went onto store all of the shortest paths and then use those to
calculate the distance. But I ended up with some replication and this did not 
tell me if a path were blocked or unreachable.

/////////////////////////////////////////////////////////////////////////////
Other notes:

Please be sure to provide feedback, regardless of the outcome.

/////////////////////////////////////////////////////////////////////////////
