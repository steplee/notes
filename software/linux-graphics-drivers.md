# Linux Graphics Drivers
## [Intel document](https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/inside-linux-graphics-paper.pdf)

X is too slow, introduce DRI for direct rendering.

	* Mesa => libGL
		* libGL is the front-end, a device driver (DRI driver) converts user calls to hardware specific calls.
	* Most of the graphics staff is userland.

	* libVA is to video-decoding what Mesa is to OpenGL.
		* libVA (= VA API) is **Intel** based, but can run on NV/AMD too.
		* AMD/NV also have proprietary standards.
		* libVA can render video to a buffer and push to application, e.g. in the form of a raw buffer, X surface, or OpenGL texture.

	* Graphics Execution Manager (GEM) is a kernel level GPU memory manager.
		* Obviously device specific.
		* exposes ioctls to user level API, which is **libDRM**

	* A 2D driver (aka DDX, mostly userspace) executes commands from Xlib (which itself is called upon by GTK, Qt, Cairo ...).
		* Primarily it does blitting.
		* usually called *xf86-video-...*
	
	* DRM (Direct Rendering Manager) is a kernel module with helper functions that call device dependent drivers.


