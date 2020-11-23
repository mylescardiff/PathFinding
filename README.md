<h1>A C++ Pathfinding Implementation using A*</h1>
<h2>The Scene</h2>
<p>
        The world is setup with light green grass tiles, dark green forest tiles, blue water tiles and a bridge. Forest tiles have a higher cost (weight), water tiles are impassible. There is only one agent on screen. It will pathfinder to the square you click in the world. In debug mode you will see the agent's node expansion as it attempts to find a way to that location. If it cannot find one (e.g. if you click the island in the middle) it will expand the entire walkable map and fail.
    </p>
    <h2>How To Run</h2>
    <ul>
        <li>Download or clone the project source</li>
        <li>Open PathFinding\PathFinding.sln </li>
        <li>Set the PathFinding project to be the startup by right clicking it in the project hierarchy and selecting <b>Set as Startup Project</b></li>
        <li>Click Play or hit F5</li>
    </ul>
    <h2>The Code</h2>
    <p>
        This is a pathfinding implementation in C++, using the <a href="https://en.wikipedia.org/wiki/A*_search_algorithm">A* Algorithm</a>. It uses my 2D game engine, Sloth Engine, for basic rendering and component based
        actors. This project uses an engine-side Grid system and an A* pathfinding algorithm build on that grid.
    </p>
    <p>
        This implementation is frame-sliced, meaning it will spread its workload over a few frames if necessary to maintain performance. You will find the implementation in <b>(SlothEngine Project) Logic\Grid\GridSystem.h</b>
    </p>
    <p>… it is in the functions <b>FindPathAStar</b> and <b>PathAStarInternal</b>. </p>
    <p><b>FindPathAStar</b> initiates the pathfinding process, and <b>PathAStarInternal</b> is called each frame while the process is still working.</p>
