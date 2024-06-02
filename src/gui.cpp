#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include "AlienFx_SDK.h"

class MainWindow : public Gtk::Window
{
public:
  MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
  virtual ~MainWindow();

protected:
  // Signal handlers:
  void on_color_set();
  void on_apply_button_pressed();
  void on_switch_state_set();

  // Member widgets:
  Gtk::Grid *m_Grid;
  Gtk::Switch *m_Switch;
  Gtk::ColorButton *m_ColorButtonLeft;
  Gtk::ColorButton *m_ColorButtonCenterLeft;
  Gtk::ColorButton *m_ColorButtonCenterRight;
  Gtk::ColorButton *m_ColorButtonRight;
  Gtk::ColorButton *m_ColorButtonAll;
  Gtk::Button *m_ApplyButton;
};

MainWindow::MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
    : Gtk::Window(cobject)
{
  builder->get_widget("mainGrid", m_Grid);
  builder->get_widget("color_switch", m_Switch);
  builder->get_widget("key_color_left", m_ColorButtonLeft);
  builder->get_widget("key_color_center_left", m_ColorButtonCenterLeft);
  builder->get_widget("key_color_center_right", m_ColorButtonCenterRight);
  builder->get_widget("key_color_right", m_ColorButtonRight);
  builder->get_widget("ZoneAll", m_ColorButtonAll);
  builder->get_widget("apply", m_ApplyButton);

  m_ColorButtonLeft->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ColorButtonCenterLeft->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ColorButtonCenterRight->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ColorButtonRight->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ApplyButton->signal_pressed().connect(sigc::mem_fun(*this, &MainWindow::on_apply_button_pressed));

  m_Switch->set_active(true);
  m_ColorButtonAll->show();
  m_Grid->hide();
  m_Switch->property_active().signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_switch_state_set));
}

MainWindow::~MainWindow()
{
}
void MainWindow::on_switch_state_set()
{
  m_ColorButtonAll->hide();
  if (m_Switch->get_active())
  {
    m_ColorButtonAll->show();
    m_Grid->hide();
    // std::cout << "Switch is ON" << std::endl;
  }
  else
  {
    m_ColorButtonAll->hide();
    m_Grid->show();
    // std::cout << "Switch is OFF" << std::endl;
  }
}

// bool on_switch_state_set(Gtk::Switch *widget, bool state)
// {
//   // Código a ser executado quando o estado do switch mudar
//   std::cout << "Switch state set to: " << (state ? "ON" : "OFF") << std::endl;
//   return false; // Retorne true para impedir outras handlers de serem executadas
// }

void MainWindow::on_color_set()
{
  // Placeholder for handling color set event.
  // Here you can update any labels or perform other actions when the color changes.
  // std::cout << "Cor alterada em um dos botões de cor." << std::endl;
}

void MainWindow::on_apply_button_pressed()
{
  AlienFx_SDK alienFX;
  // std::cout << "Botão aplicar pressionado. Cores selecionadas:" << std::endl;

  Gdk::RGBA colorLeft = m_ColorButtonLeft->get_rgba();
  Gdk::RGBA colorCenterLeft = m_ColorButtonCenterLeft->get_rgba();
  Gdk::RGBA colorCenterRight = m_ColorButtonCenterRight->get_rgba();
  Gdk::RGBA colorRight = m_ColorButtonRight->get_rgba();
  Gdk::RGBA colorAll = m_ColorButtonAll->get_rgba();

  std::map<std::string, std::vector<int>> zones;
  zones["0"] = {static_cast<int>(colorLeft.get_red() * 255),
                static_cast<int>(colorLeft.get_green() * 255),
                static_cast<int>(colorLeft.get_blue() * 255)};
  zones["1"] = {static_cast<int>(colorCenterLeft.get_red() * 255),
                static_cast<int>(colorCenterLeft.get_green() * 255),
                static_cast<int>(colorCenterLeft.get_blue() * 255)};
  zones["2"] = {static_cast<int>(colorCenterRight.get_red() * 255),
                static_cast<int>(colorCenterRight.get_green() * 255),
                static_cast<int>(colorCenterRight.get_blue() * 255)};
  zones["3"] = {static_cast<int>(colorRight.get_red() * 255),
                static_cast<int>(colorRight.get_green() * 255),
                static_cast<int>(colorRight.get_blue() * 255)};

  if (m_Switch->get_active())
  {
    alienFX.SetColorAll(colorAll.get_red() * 255, colorAll.get_green() * 255, colorAll.get_blue() * 255);
  }
  else
  {
    alienFX.SetColorZones(zones);
  }
}

int main(int argc, char *argv[])
{

  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
  try
  {
    builder->add_from_file("layout.glade");
  }
  catch (const Glib::FileError &ex)
  {
    std::cerr << "Erro ao carregar o arquivo Glade: " << ex.what() << std::endl;
    return 1;
  }

  MainWindow *window = nullptr;
  builder->get_widget_derived("main_window", window);

  if (!window)
  {
    std::cerr << "Erro ao instanciar a janela principal." << std::endl;
    return 1;
  }

  return app->run(*window);
}
