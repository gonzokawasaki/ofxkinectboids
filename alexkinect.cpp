
#include <XnOS.h>
#include <XnCppWrapper.h>
#include <ofxOpenNI.h>
#include <alexkinect.h>

bool OpenNiNode::initialise()
{
	// initialise the context
	
	if( mContext.Init() != XN_STATUS_OK )
	{
		return( false );
	}

	// we want to mirror the image from the Kinect
	
	mContext.SetGlobalMirror( true );

	// Tell the context we want depth information
	
	if( mGeneratorDepth.Create( mContext ) != XN_STATUS_OK )
	{
		return( false );
	}

	// Get accees to the depth meta information
	
	mGeneratorDepth.GetMetaData( mMetaDataDepth );

	// Start the Kinect
	
	if( mContext.StartGeneratingAll() != XN_STATUS_OK )
	{
		return( false );
	}

	return( true );
}

void OpenNiNode::frameStart()
{
	// This routine gets called every frame so I use WaitNoneUpdateAll()
	// You might instead want to use WaitOneUpdateAll()
	
	if( mContext.WaitNoneUpdateAll() != XN_STATUS_OK )
	{
		return;
	}

	// the size of the depth image (in pixels) is available using
	// mMetaDataDepth.FullXRes() and mMetaDataDepth.FullYRes()

	// tell the depth generator to get the frame of depth information
	
	mGeneratorDepth.GetMetaData( mMetaDataDepth );

	// the raw 16-bit depth values can now be accessed at mMetaDataDepth.Data()
}
