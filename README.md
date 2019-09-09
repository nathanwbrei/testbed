
A simple suite exploring ROOT input option(s) for JANA
======================================================

Compile
-------

```
  mkdir build && cd build
  cmake -DJANA=<jana-installation-directory> -Wno-dev ..
  make -j4
  export JANA_PLUGIN_PATH=${PWD}
```

Create input tree
-----------------

```
  ./writer  # a simple ROOT tree with 10^6 double entries
```

Read the tree
-------------

```  
  All of these create histograms.root with a single histogram 'hv', 
  but a TTree input loop is done in a very different way;
```

```
  # Standalone loop in ROOT environment; several options available;
  ./reader1 # straightforward single-threaded loop
```

  ./reader2 # 4 threads using TTreeProcessorMT interface

  ./reader3 # 4 threads using std::thread interface manually

  ./reader4 # 4 threads using RDataFrame interface

  # JANA loop; make sure 'jana' is in the PATH, of course; either of the 
  # two commands below should work; the first one is "naive"; the second 
  # one uses asynchronous processor and JANA Get() interface;
  jana -Pplugins=libjreader -Pnthreads=4 /dev/zero
  jana -Pplugins=libjreader -Pnthreads=4 -Pwith-processor=yes /dev/zero


  # plot the same 'hv' histogram after any of the 'reader*' passes above
  root -l ../plotter.C

