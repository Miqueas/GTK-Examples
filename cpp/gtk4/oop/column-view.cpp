#include <print>
#include <gtkmm.h>
#include <iostream>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.OOP.ColumnView";
static const Glib::ustring APP_TITLE = "Gtk::ColumnView";

class App : public Gtk::Application {
  public:
    static Glib::RefPtr<App> create() {
      return Glib::make_refptr_for_instance<App>(new App());
    }

  protected:
    App() : Gtk::Application(APP_ID) {}

    void on_startup() override {
      // Ensures chain-up
      Gtk::Application::on_startup();

      auto list_model = Gtk::StringList::create();
      auto selection_model = Gtk::NoSelection::create(list_model);
      auto key_factory = Gtk::SignalListItemFactory::create();
      auto value_factory = Gtk::SignalListItemFactory::create();
      auto window = Gtk::make_managed<Gtk::ApplicationWindow>();
      auto scroll = Gtk::make_managed<Gtk::ScrolledWindow>();
      auto column_view = Gtk::make_managed<Gtk::ColumnView>(selection_model);
      auto key_column = Gtk::ColumnViewColumn::create("Key", key_factory);
      auto value_column = Gtk::ColumnViewColumn::create("Value", value_factory);

      for (guint8 i = 0; i < G_MAXUINT8; i++) list_model->append(Glib::ustring::format(i));

      key_factory->signal_setup().connect(sigc::mem_fun(*this, &App::on_factory_setup));
      key_factory->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &App::on_factory_bind), "Key"));

      value_factory->signal_setup().connect(sigc::mem_fun(*this, &App::on_factory_setup));
      value_factory->signal_bind().connect(sigc::bind(sigc::mem_fun(*this, &App::on_factory_bind), "Value"));

      window->set_child(*scroll);
      window->set_title(APP_TITLE);
      window->set_default_size(400, 400);

      scroll->set_child(*column_view);
      
      column_view->set_reorderable(false);
      column_view->set_show_row_separators(true);
      column_view->set_show_column_separators(true);
      column_view->append_column(key_column);
      column_view->append_column(value_column);

      key_column->set_expand(true);
      value_column->set_expand(true);

      add_window(*window);
    }

    void on_activate() override {
      Gtk::Window* window = get_active_window();
      if (window != nullptr) window->present();
    }

  private:
    void on_factory_setup(const Glib::RefPtr<Gtk::ListItem>& list_item) {
      auto label = Gtk::make_managed<Gtk::Label>("");
      label->set_halign(Gtk::Align::START);
      list_item->set_child(*label);
    }

    void on_factory_bind(const Glib::RefPtr<Gtk::ListItem>& list_item, Glib::ustring name) {
      auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
      auto string_object = std::dynamic_pointer_cast<Gtk::StringObject>(list_item->get_item());
      label->set_label(name + ": " + string_object->get_string());
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}