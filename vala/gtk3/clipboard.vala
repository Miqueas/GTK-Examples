const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Clipboard";
const string appTitle = "GtkClipboard";

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

  with (window) {
    add(box);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(entry, false, false, 0);
    pack_start(buttonBox, false, false, 0);
  }

  with (buttonBox) {
    layout_style = Gtk.ButtonBoxStyle.EXPAND;
    pack_start(copyButton, true, true, 0);
    pack_start(setButton, true, true, 0);
  }

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