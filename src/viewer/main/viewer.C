/*****************************************************************************
*
* Copyright (c) 2000 - 2019, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                                 viewer.C                                  //
// ************************************************************************* //

#include <visit-config.h>
#include <cstdio>
#include <cstdlib>

#include <qapplication.h>
#include <QStringList>

#include <VisItViewer.h>
#include <AppearanceAttributes.h>
#include <DebugStream.h>
#include <LostConnectionException.h>
#include <ViewerMethods.h>
#include <ViewerState.h>
#include <VisItException.h>

#include <QVTKOpenGLWidget.h>

// ****************************************************************************
// Method: Viewer_LogQtMessages
//
// Purpose: 
//   Message handler that routes Qt messages to the debug logs.
//
// Arguments:
//   type : The message type.
//   msg  : The message.
//
// Programmer: Brad Whitlock
// Creation:   Thu Mar 15 18:17:47 PST 2007
//
// Modifications:
//   
// ****************************************************************************

static void
Viewer_LogQtMessages(QtMsgType type, const QMessageLogContext &context, const QString& msg)
{
    switch(type)
    {
    case QtInfoMsg:
        debug1 << "Qt: Info: " << msg.toStdString() << endl;
        break;
    case QtDebugMsg:
        debug1 << "Qt: Debug: " << msg.toStdString() << endl;
        break;
    case QtWarningMsg:
        debug1 << "Qt: Warning: " << msg.toStdString() << endl;
        break;
    case QtCriticalMsg:
        debug1 << "Qt: Critical: " << msg.toStdString() << endl;
        break;
    case QtFatalMsg:
        debug1 << "Qt: Fatal: " << msg.toStdString() << endl;
        abort(); // HOOKS_IGNORE
        break;
    }
}


// ****************************************************************************
//  Method: ViewerMain
//
//  Purpose:
//      The viewer main program.
//
//  Arguments:
//      argc    The number of command line arguments.
//      argv    The command line arguments.
//
//  Programmer: Eric Brugger
//  Creation:   August 16, 2000
//
//  Modifications:
//    Brad Whitlock, Thu Aug 14 10:09:17 PDT 2008
//    Rewrote so it uses the VisItViewer class, which encapsulates some of 
//    the stuff needed to set up the viewer. The new design permits us to 
//    embed the viewer in other Qt applications.
//
//    Jeremy Meredith, Thu Oct 16 19:29:12 EDT 2008
//    Added a flag for whether or not ProcessCommandLine should force 
//    the identical version.  It's necessary for new viewer-apps but
//    might confuse VisIt-proper's smart versioning.
//
//    Brad Whitlock, Wed Nov 19 13:47:22 PST 2008
//    Prevent Qt from getting the -geometry flag since it messes up the
//    viswin's initial size on X11 with Qt 4.
//
//    Brad Whitlock, Thu Apr  9 14:19:51 PDT 2009
//    Skip connecting to the client if we're doing a -connectengine, which
//    means the engine and not the client is launching the viewer.
//
//    Tom Fogal, Sun Jan 24 17:10:46 MST 2010
//    Add two new Qt arguments, to tell Qt the application name.  Patch from
//    Andreas Kloeckner, I modified it to use strdup().
//
//    Cyrus Harrison, Fri Oct 11 15:40:29 PDT 2013
//    Clear any static lib paths (QCoreApplication::libraryPaths) to avoid
//    conflicts with loading qt after a make install or make package
//
//    Kathleen Biagas, Thu Jan 14 12:30:29 PST 2016
//    If running on linux in nowin mode, with qt 5, add -platform minimal
//    to the QApplication arguments.
//
//    Kathleen Biagas, Wed Feb  7 10:40:52 PST 2018
//    Set default QSurfaceFormat, required to be set before instantiating
//    QApplication, due to our use of QVTKOpenGLWidget.
//
//    Kevin Griffin, Thu Mar 15 19:56:39 PDT 2018
//    Made the viewer no longer responsible for removing the crash session
//    files. The GUI has the sole responsiblity for removing the crash
//    session files on exit.
//
// ****************************************************************************

int
ViewerMain(int argc, char *argv[])
{
    int retval = 0;

    //
    // Do basic initialization. This is only done once to initialize the
    // viewer library.
    //
    VisItViewer::Initialize(&argc, &argv);

    TRY
    {
        //
        // Create the viewer.
        //
        VisItViewer viewer;

        //
        // Connect back to the client if we're not doing a reverse launch from
        // the compute engine.
        //
        bool reverseLaunch = false;
        for(int i = 1; i < argc && !reverseLaunch; ++i)
            reverseLaunch |= (strcmp(argv[i], "-connectengine") == 0);
        
        if(!reverseLaunch)
            viewer.Connect(&argc, &argv);

        //
        // Process the command line arguments first since some may be removed
        // by QApplication::QApplication.
        //
        viewer.ProcessCommandLine(argc, argv, false);

        //
        // Create the QApplication. This sets the qApp pointer.
        //
        bool add_platform_arg = false;

        int nExtraArgs = 5;
// Instead of being exclusionary, should the check insted be
// #if defined(Q_OS_LINUX) ??
#if !defined(_WIN32) && !defined(Q_OS_MAC)
        if (viewer.GetNowinMode())
        {
            // really only need this if X11 not running, but how to test?
            add_platform_arg = true;
            nExtraArgs += 2;
        }
#endif
        
        char **argv2 = new char *[argc + nExtraArgs];
        int real_argc = 0;
        for(int i = 0; i < argc; ++i)
        {
            if(strcmp(argv[i], "-geometry") == 0)
                ++i;
            else
                argv2[real_argc++] = argv[i];
        }

        argv2[real_argc] = (char*)"-font";
        argv2[real_argc+1] = (char*)viewer.State()->GetAppearanceAttributes()->GetFontName().c_str();
        argv2[real_argc+2] = (char*)"-name";
        argv2[real_argc+3] = (char*)"visit-viewer";
        if (add_platform_arg)
        {
            argv2[real_argc+4] = (char*)"-platform";
            argv2[real_argc+5] = (char*)"minimal";
        }
        argv2[real_argc+nExtraArgs-1] = NULL;

        debug1 << "Viewer using font: " << argv2[real_argc+1] << endl;
        qInstallMessageHandler(Viewer_LogQtMessages);
        int argc2 = real_argc + nExtraArgs;

        // Setting default QSurfaceFormat required with QVTKOpenGLwidget
        auto surfaceFormat = QVTKOpenGLWidget::defaultFormat();
        surfaceFormat.setSamples(0);
        surfaceFormat.setAlphaBufferSize(0);
        QSurfaceFormat::setDefaultFormat(surfaceFormat);

        QApplication *mainApp = new QApplication(argc2, argv2, !viewer.GetNowinMode());

        //
        // Now that we've created the QApplication, let's call the viewer's
        // setup routine.
        //
        viewer.Setup();

        //
        // Execute the viewer.
        //
        bool keepGoing = true;
        while (keepGoing)
        {
            TRY
            { 
                retval = mainApp->exec();
                keepGoing = false;
            }
            CATCH(LostConnectionException)
            {
                cerr << "The component that launched VisIt's viewer has terminated "
                        "abnormally." << endl;
                keepGoing = false;
                retval = -1;
            }
            CATCH2(VisItException, ve)
            {
                QString msg = QObject::tr("VisIt has encountered the following error: %1.\n"
                    "VisIt will attempt to continue processing, but it may "
                    "behave unreliably.  Please save this error message and "
                    "give it to a VisIt developer.  In addition, you may want "
                    "to save your session and re-start.  Of course, this "
                    "session may still cause VisIt to malfunction.").
                    arg(ve.Message().c_str());
                viewer.Error(msg);
                keepGoing = true;
            }
            ENDTRY
        }
    }
    CATCH2(VisItException, e)
    {
        debug1 << "VisIt's viewer encountered the following fatal "
                  "initialization error: " << endl
               << e.Message().c_str() << endl;
        retval = -1;
    }
    ENDTRY

    // Finalize the viewer library.
    VisItViewer::Finalize();

    return retval;
}

// ****************************************************************************
// Method: main/WinMain
//
// Purpose: 
//   The program entry point function.
//
// Programmer: Brad Whitlock
// Creation:   Wed Nov 23 13:15:31 PST 2011
//
// Modifications:
//   
// ****************************************************************************

#if defined(_WIN32) && defined(VISIT_WINDOWS_APPLICATION)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int WINAPI
WinMain(HINSTANCE hInstance,     // handle to the current instance
        HINSTANCE hPrevInstance, // handle to the previous instance    
        LPSTR lpCmdLine,         // pointer to the command line
        int nCmdShow             // show state of window
)
{
    return ViewerMain(__argc, __argv);
}
#else
int
main(int argc, char *argv[])
{
    return ViewerMain(argc, argv);
}
#endif



