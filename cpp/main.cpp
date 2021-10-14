#include "Common.h"
#include <clipp.h>

#include <map>
#include <fmt/format.h>

#include <mutils/ui/sdl_imgui_starter.h>
#include <mutils/file/runtree.h>
#include <mutils/time/profiler.h>

#include <implot.h>
using namespace std;
using namespace MUtils;
using namespace MUtils::Profiler;
using namespace clipp;

std::string g_CurrentProblem;

Object* g_pObject = nullptr;
class App : public IAppStarterClient
{
public:
    App()
    {

        m_settings.flags |= AppStarterFlags::DockingEnable;
        m_settings.startSize = NVec2i(1680, 1000);
        m_settings.clearColor = NVec4f(.25, .25, .25, 1.0f);
    }

    // Inherited via IAppStarterClient
    virtual fs::path GetRootPath() const override
    {
        // TODO: FIX!
        bool bDev = true;
        if (bDev)
        {
            return PRACTICE_ROOT;
        }
        else
        {
            // Setup app runtree
            return SDL_GetBasePath();
        }
    }

    virtual void AddFonts(float size_pixels, const ImFontConfig* pConfig, const ImWchar* pRanges) override
    {
        auto fontPath = this->GetRootPath() / "run_tree" / "fonts" / "Roboto-Regular.ttf";
        m_pCanvasFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath.string().c_str(), size_pixels, pConfig, pRanges);
    }

    virtual void InitBeforeDraw() override
    {
        ImPlot::CreateContext();
    }

    virtual void InitDuringDraw() override
    {
        LOG(INFO, "Init");

        m_settingsPath = file_init_settings("practice", runtree_path() / "settings" / "settings.toml");
    }

    virtual void Update(float duration, const NVec2i& displaySize) override
    {

    }

    virtual void Destroy() override
    {
        ImPlot::DestroyContext();
        MUtils::Profiler::Finish();
        delete g_pObject;
    }

    virtual void Draw(const NVec2i& displaySize) override
    {
        /* Nothing - 3D*/
    }

    virtual void DrawGUI(const NVec2i& displaySize) override
    {
        PROFILE_SCOPE(Gui);
        static bool p_open = true;
        m_displaySize = displaySize;

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu(fmt::format("FPS: {:.0f}", ImGui::GetIO().Framerate).c_str()))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        bool open = true;
        Profiler::ShowProfile(&open);

        static int warmUp = 0;
        if (warmUp > 0)
        {
            if (g_pObject)
            {
                if (warmUp == 1)
                {
                    g_pObject->RunOnce();
                }
                g_pObject->Run();
                g_pObject->DrawGUI();


                if (warmUp == 2)
                {
                    Profiler::SetPaused(true);
                }
            }
        }
        warmUp++;

        ImGui::End();
    }

    virtual void KeyEvent(const SDL_KeyboardEvent& ev) override
    {
        PROFILE_SCOPE(KeyEvent);
        if (ev.repeat > 0)
        {
            return;
        }
    }

    virtual AppStarterSettings& GetSettings() override
    {
        return m_settings;
    }

private:
    AppStarterSettings m_settings;
    NVec2i m_displaySize;
    fs::path m_settingsPath;
    ImFont* m_pCanvasFont = nullptr;
    std::string m_pendingLayoutLoad;
};

App theApp;

int main(int argc, char** argv)
{

    MUtils::Profiler::Init();

    // Parse the command line
    std::string problem;
    std::string data;
    auto cli = group(
        value("problem", problem)
    );

    if (parse(argc, argv, cli) && !problem.empty())
    {
        ObjectFactory* pFactory = nullptr;
        for (auto& p : Object::GetFactories())
        {
            if (p.first == problem)
            {
                pFactory = p.second;
            }
        }

        if (pFactory == nullptr)
        {
            LOG(ERROR, problem << " problem not found!");
            return 1;
        }

        LOG(INFO, "\nProblem: " << problem);
        g_CurrentProblem = problem;
        g_pObject = pFactory->create();
    }
    else
    {
        LOG(ERROR, "Failed to parse commandline");
    }

    return sdl_imgui_start(argc, argv, gsl::not_null<MUtils::IAppStarterClient*>(&theApp));
}

