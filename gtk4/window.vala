void main() {
  Gtk.init();

  var win = new Gtk.Window();
  win.set_default_size(400, 400);
  win.present();

  while (Gtk.Window.get_toplevels().get_n_items() > 0)
    MainContext.get_thread_default().iteration(true);
}