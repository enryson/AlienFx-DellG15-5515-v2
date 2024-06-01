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

  // Member widgets:
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
  

  builder->get_widget("key_color_left", m_ColorButtonLeft);
  builder->get_widget("key_color_center_left", m_ColorButtonCenterLeft);
  builder->get_widget("key_color_center_right", m_ColorButtonCenterRight);
  builder->get_widget("key_color_right", m_ColorButtonRight);
  builder->get_widget("ZoneAll", m_ColorButtonAll);
  builder->get_widget("apply", m_ApplyButton);

  if (!m_ColorButtonLeft || !m_ColorButtonCenterLeft || !m_ColorButtonCenterRight || !m_ColorButtonRight || !m_ApplyButton)
  {
    std::cerr << "Erro ao carregar os widgets do arquivo Glade." << std::endl;
    std::exit(1);
  }

  m_ColorButtonLeft->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ColorButtonCenterLeft->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ColorButtonCenterRight->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ColorButtonRight->signal_color_set().connect(sigc::mem_fun(*this, &MainWindow::on_color_set));
  m_ApplyButton->signal_pressed().connect(sigc::mem_fun(*this, &MainWindow::on_apply_button_pressed));
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_color_set()
{
  // Placeholder for handling color set event.
  // Here you can update any labels or perform other actions when the color changes.
  std::cout << "Cor alterada em um dos botões de cor." << std::endl;
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
  zones["0"] = {colorLeft.get_red() * 255, colorLeft.get_green() * 255, colorLeft.get_blue() * 255};
  zones["1"] = {colorCenterLeft.get_red() * 255, colorCenterLeft.get_green() * 255, colorCenterLeft.get_blue() * 255};
  zones["2"] = {colorCenterRight.get_red() * 255, colorCenterRight.get_green() * 255, colorCenterRight.get_blue() * 255};
  zones["3"] = {colorRight.get_red() * 255, colorRight.get_green() * 255, colorRight.get_blue() * 255};
  alienFX.SetColorZones(zones);
  // std::cout << "Esquerda: R=" << colorLeft.get_red() * 255 << ", G=" << colorLeft.get_green() * 255 << ", B=" << colorLeft.get_blue() * 255 << std::endl;
  // std::cout << "Centro Esquerda: R=" << colorCenterLeft.get_red() * 255 << ", G=" << colorCenterLeft.get_green() * 255 << ", B=" << colorCenterLeft.get_blue() * 255 << std::endl;
  // std::cout << "Centro Direita: R=" << colorCenterRight.get_red() * 255 << ", G=" << colorCenterRight.get_green() * 255 << ", B=" << colorCenterRight.get_blue() * 255 << std::endl;
  // std::cout << "Direita: R=" << colorRight.get_red() * 255 << ", G=" << colorRight.get_green() * 255 << ", B=" << colorRight.get_blue() * 255 << std::endl;

  // alienFX.SetColorZones(zones);

  // alienFX.SetColorAll(colorAll.get_red()* 255 , colorAll.get_green()* 255 , colorAll.get_blue()* 255 );
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
