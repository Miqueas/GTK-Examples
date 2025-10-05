const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.EntryCompletion";
const string APP_TITLE = "Gtk.Entry";
const string[] items = { "GNOME", "Vala", "GTK", "Example", "Entry", "Completion" };

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void on_app_startup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var entryCompletionModel = new Gtk.ListStore(1, typeof(string));
  var entryCompletion = new Gtk.EntryCompletion();
  var entry = new Gtk.Entry();
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  Gtk.TreeIter iter;

  window.add(box);
  window.title = APP_TITLE;
  window.set_default_size(400, 400);

  foreach (var name in items) {
    entryCompletionModel.append(out iter);
    entryCompletionModel.set(iter, 0, name);
  }

  entryCompletion.model = entryCompletionModel;
  entryCompletion.text_column = 0;
  entryCompletion.popup_completion = true;

  entry.completion = entryCompletion;

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(new Gtk.Label("Try typing \"gnome\" or \"gtk\""), false, false);
  box.pack_start(entry, false, false);
  box.show_all();
}