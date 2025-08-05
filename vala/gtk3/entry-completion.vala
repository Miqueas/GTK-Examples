const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.EntryCompletion";
const string appTitle = "GtkEntry";
const string[] items = { "GNOME", "Vala", "GTK", "Example", "Entry", "Completion" };

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onAppStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var headerBar = new Gtk.HeaderBar();
  var entryCompletionModel = new Gtk.ListStore(1, typeof(string));
  var entryCompletion = new Gtk.EntryCompletion();
  var entry = new Gtk.Entry();
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  Gtk.TreeIter iter;

  with (window) {
    add(box);
    set_titlebar(headerBar);
    set_default_size(400, 400);
  }

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }

  foreach (var name in items) {
    entryCompletionModel.append(out iter);
    entryCompletionModel.set(iter, 0, name);
  }

  with (entryCompletion) {
    model = entryCompletionModel;
    text_column = 0;
    popup_completion = true;
  }

  entry.completion = entryCompletion;

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(new Gtk.Label("Try typing \"gnome\" or \"gtk\""), false);
    pack_start(entry, false);
    show_all();
  }
}