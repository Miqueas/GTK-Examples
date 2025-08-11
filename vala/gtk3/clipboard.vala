const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Clipboard";
const string appTitle = "Gtk.Clipboard";

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
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var entry = new Gtk.Entry();
  var buttonBox = new Gtk.ButtonBox(Gtk.Orientation.HORIZONTAL);
  var copyButton = new Gtk.Button.with_label("Copy to Clipboard");
  var setButton = new Gtk.Button.with_label("Set from Clipboard");
  var clipboard = Gtk.Clipboard.get_default(Gdk.Display.get_default());

  window.add(box);
  window.title = appTitle;
  window.border_width = 10;
  window.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(entry, false, false, 0);
  box.pack_start(buttonBox, false, false, 0);

  buttonBox.layout_style = Gtk.ButtonBoxStyle.EXPAND;
  buttonBox.pack_start(copyButton, true, true, 0);
  buttonBox.pack_start(setButton, true, true, 0);

  copyButton.clicked.connect(() => {
    clipboard.set_text(entry.text, -1);
    entry.grab_focus();
    print("Text copied to clipboard: %s\n", entry.text);
  });

  setButton.clicked.connect(() => {
    var text = clipboard.wait_for_text();

    if (text == null) {
      print("No text found in clipboard.\n");
      return;
    }

    entry.text = text;
    entry.grab_focus();
    print("Text set from clipboard: %s\n", text);
  });

  box.show_all();
}