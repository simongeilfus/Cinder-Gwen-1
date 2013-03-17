Cinder-Gwen
===========
A Cinder block for Garry Newman's pretty fantastic [GWEN](https://github.com/garrynewman/GWEN)

### Status: alpha

The the cinder [GL renderer](GwenRendererGl.cpp) and [input](GwenInput.cpp) are both fully functional on desktop - iOS support is still to come.  The gwen [platform-specific](CinderGwen.cpp) stuff is still a work in progress, although it isn't crucial for usage. Although my usage of gwen has been short so far, it looks to be one of the best existing, full featured, well abstracted gui's available to us cinder users.

### To build

```
git clone --recursive git://github.com/reakinator/Cinder-Gwen.git $CINDER_PATH/blocks/gwen
```

The `--recursive` is to pull down the gwen git repo as well, since it is referenced as a submodule. 

Currently requires [cinder](https://github.com/reakinator/Cinder) from source, with the latest dev branch (currently at 746dcefbe).  The samples expect this repo to be within the cinder/blocks folder, and if it is there, you can use tinderbox to automatically add Gwen and it's cinder implementation to your project.

### File issues please

I'm still working on how best to package this, so let me know what you think.  Please file issues as they come up, or better yet the beloved pull requests. Thanks!


### License

[Same as Gwen](https://github.com/garrynewman/GWEN/blob/master/LICENSE.md) (MIT)