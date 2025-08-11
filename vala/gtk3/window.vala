const string appTitle = "Gtk.Window";

void main(string[] args) {
  Gtk.init(ref args);

  var window = new Gtk.Window();
  window.title = appTitle;
  window.set_default_size(400, 400);
  window.destroy.connect(Gtk.main_quit);
  window.present();

  Gtk.main();
}