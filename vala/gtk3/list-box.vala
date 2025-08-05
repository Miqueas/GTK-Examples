const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ListBox";
const string appTitle = "GtkListBox";

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
  var listBox = new Gtk.ListBox();
  var scrolledWindow = new Gtk.ScrolledWindow(null, null);
  var button = new Gtk.Button.with_label("Load");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  with (window) {
    border_width = 10;
    add(box);
    set_titlebar(headerBar);
    set_default_size(400, 400);
  }

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }

  with (scrolledWindow) {
    shadow_type = Gtk.ShadowType.NONE;
    propagate_natural_width = true;
    propagate_natural_height = true;
    add(listBox);
  }

  with (button) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    clicked.connect(self => {
      for (int i = 0; i < 100; i++)
        listBox.insert(new Gtk.Label(@"Text $(i + 1)") { visible = true }, i);
    });
  }

  with (box) {
    pack_start(scrolledWindow, true, true, 0);
    pack_start(button, false, false, 0);
    show_all();
  }
}