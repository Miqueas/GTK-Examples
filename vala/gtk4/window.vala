const string appTitle = "GtkWindow";

void main() {
  Gtk.init();

  var window = new Gtk.Window();
  window.title = appTitle;
  window.set_default_size(400, 400);
  window.present();

  while (Gtk.Window.get_toplevels().get_n_items() > 0)
    MainContext.get_thread_default().iteration(true);
}