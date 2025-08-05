const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.FlowBox";
const string appTitle = "GtkFlowBox";
const string[] icons = {
  "face-angel",
  "face-angry",
  "face-surprise",
  "face-laugh",
  "face-plain",
  "face-sad",
  "face-cool",
  "face-smirk",
  "face-sick",
  "face-kiss",
  "face-heart-broken",
  "face-smile",
  "face-crying",
  "face-devilish",
  "face-heart",
  "face-sad",
  "face-smile-big",
  "face-tired",
  "face-wink",
  "face-worried"
};

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
  var flowBox = new Gtk.FlowBox();
  var scrolledWindow = new Gtk.ScrolledWindow(null, null);

  with (window) {
    add(scrolledWindow);
    set_titlebar(headerBar);
    set_default_size(400, 400);
  }

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }

  with (flowBox) {
    set_selection_mode(Gtk.SelectionMode.NONE);
    set_max_children_per_line(30);

    for (var i = 0; i < 1000; i++)
      insert(new Gtk.Image.from_icon_name(icons[Random.int_range(0, 20)], Gtk.IconSize.DIALOG), i);
  }

  with (scrolledWindow) {
    add(flowBox);
    set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC);
    show_all();
  }
}