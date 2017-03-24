#include "pch.h"


int g_Width, g_Height;


#ifdef NOESIS_GUI

// All NoesisGUI API is under Noesis namespace
using namespace Noesis;

// This is the main view that displays the content
Ptr<Noesis::IView> g_XamlView;

// Error handler are invoked for fatal errors. You must never return from here
void NoesisErrorHandler(const NsChar* filename, NsSize line, const NsChar* desc, NsBool fatal)
{
    printf("\nERROR: %s\n\n", desc);
}

void Noesis_Init()
{
    // NoesisGUI is initialized here. Resources will be loaded from current working directory
    Noesis::GUI::Init(NoesisErrorHandler);
    Noesis::GUI::SetResourceProvider("..");

    // Loads XAML and creates a view with it
    Ptr<FrameworkElement> xaml = Noesis::GUI::LoadXaml<FrameworkElement>("PasswordBox.xaml");
    g_XamlView = Noesis::GUI::CreateView(xaml.GetPtr());
    g_XamlView->SetAntialiasingMode(Noesis::Gui::AntialiasingMode_PPAA);

    // Initializes renderer. This could be done in a render thread
    Ptr<GLRenderDevice> device = *new GLRenderDevice();
    Ptr<VGContext> context = Noesis::GUI::CreateVGContext(device.GetPtr(), Noesis::VGOptions());
    g_XamlView->GetRenderer()->Init(context.GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Noesis_Shutdown()
{
    // Free global resources and shutdown kernel
    g_XamlView.Reset();
    Noesis::GUI::Shutdown();
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayFunc(void)
{
#ifdef NOESIS_GUI
    // Updates view passing global time
    g_XamlView->Update(glutGet(GLUT_ELAPSED_TIME) / 1000.0);

    // Performs rendering operations. Note that the renderer associated to a view is intended
    // to be used in the render thread. In this simple application it is the main thread
    Noesis::IRenderer* renderer = g_XamlView->GetRenderer();

    // Applies changes to the render tree
    renderer->UpdateRenderTree();

    // Renders offscreen textures. This step must be done before binding the main render target
    if (renderer->NeedsOffscreen())
    {
        renderer->RenderOffscreen();
    }
#endif

    // Restore state. This must be done per frame because NoesisGUI modifies the GPU state
    // TODO: improve this by adding a SaveState() and RestoreState() to GLRenderDevice
    glClearColor(0.0f, 0.0f, 0.25f, 0.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glViewport(0, 0, g_Width, g_Height);

#ifdef NOESIS_GUI
    // Renders UI to active render target in the active viewport
    renderer->Render();
#endif

    glutSwapBuffers();
    glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ReshapeFunc(int width, int height)
{
    g_Width = width;
    g_Height= height;

#ifdef NOESIS_GUI
    if (g_XamlView != 0)
    {
        g_XamlView->SetSize(width, height);
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseMoveFunc(int x, int y)
{
#ifdef NOESIS_GUI
    if (g_XamlView != 0)
    {
        g_XamlView->MouseMove(x, y);
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseFunc(int button, int state, int x, int y)
{
#ifdef NOESIS_GUI
    if (g_XamlView != 0)
    {
        Noesis::MouseButton b = button == GLUT_LEFT_BUTTON ? Noesis::MouseButton_Left:
            button == GLUT_MIDDLE_BUTTON ? Noesis::MouseButton_Middle:
            Noesis::MouseButton_Right;

        if (state == GLUT_DOWN)
        {
            g_XamlView->MouseButtonDown(x, y, b);
        }
        else
        {
            g_XamlView->MouseButtonUp(x, y, b);
        }
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyboardFunc(unsigned char key, int x, int y)
{
#ifdef NOESIS_GUI
    if (g_XamlView != 0)
    {
        if (key == '\t')
        {
            g_XamlView->KeyDown(Noesis::Key::Key_Tab);
        }
        else if (key == '\b')
        {
            g_XamlView->KeyDown(Noesis::Key::Key_Back);
        }
        else
        {
            g_XamlView->Char(key);
        }
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyboardUpFunc(unsigned char key, int x, int y)
{
#ifdef NOESIS_GUI
    if (g_XamlView != 0)
    {
        if (key == '\t')
        {
            g_XamlView->KeyUp(Noesis::Key::Key_Tab);
        }
        else if (key == '\b')
        {
            g_XamlView->KeyUp(Noesis::Key::Key_Back);
        }
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    // Window creation
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("NoesisGUI");

#ifdef NOESIS_GUI
    Noesis_Init();
    atexit(Noesis_Shutdown);
#endif

    // GLUT callbacks
    glutDisplayFunc(&DisplayFunc);
    glutReshapeFunc(&ReshapeFunc);
    glutPassiveMotionFunc(&MouseMoveFunc);
    glutMouseFunc(&MouseFunc);
    glutKeyboardFunc(&KeyboardFunc);
    glutKeyboardUpFunc(&KeyboardUpFunc);

    glutMainLoop();
    return 0;
}
