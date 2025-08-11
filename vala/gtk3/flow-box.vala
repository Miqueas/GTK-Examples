const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.FlowBox";
const string appTitle = "Gtk.FlowBox";
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
  var flowBox = new Gtk.FlowBox();
  var scrolledWindow = new Gtk.ScrolledWindow(null, null);

  window.add(scrolledWindow);
  window.title = appTitle;
  window.set_default_size(400, 400);

  flowBox.set_selection_mode(Gtk.SelectionMode.NONE);
  flowBox.set_max_children_per_line(30);

  for (var i = 0; i < 1000; i++) {
    var random = Random.int_range(0, icons.length);
    flowBox.insert(
      new Gtk.Image.from_icon_name(icons[random], Gtk.IconSize.DIALOG),
      i
    );
  }

  scrolledWindow.add(flowBox);
  scrolledWindow.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC);
  scrolledWindow.show_all();
}