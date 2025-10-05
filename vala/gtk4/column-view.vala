const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.ColumnView";
const string APP_TITLE = "Gtk.ColumnView";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  Gtk.Window? window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void on_app_startup(Application self) {
  var list_model = new Gtk.StringList(null);
  var selection_model = new Gtk.NoSelection(list_model);
  var key_factory = new Gtk.SignalListItemFactory();
  var value_factory = new Gtk.SignalListItemFactory();
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var scroll = new Gtk.ScrolledWindow();
  var column_view = new Gtk.ColumnView(selection_model);
  var key_column = new Gtk.ColumnViewColumn("Key", key_factory);
  var value_column = new Gtk.ColumnViewColumn("Value", value_factory);

  for (uint8 i = 0; i < uint8.MAX; i++) list_model.append(@"$(i)");

  key_factory.setup.connect(on_setup_item);
  key_factory.bind.connect((object) => {
    var list_item = object as Gtk.ListItem;
    var label = list_item.child as Gtk.Label;
    var item = list_item.item as Gtk.StringObject;
    label.label = @"Key: $(item.string)";
  });
  
  value_factory.setup.connect(on_setup_item);
  value_factory.bind.connect((object) => {
    var list_item = object as Gtk.ListItem;
    var label = list_item.child as Gtk.Label;
    var item = list_item.item as Gtk.StringObject;
    label.label = @"Value: $(item.string)";
  });

  window.title = APP_TITLE;
  window.child = scroll;
  window.set_default_size(400, 400);

  scroll.child = column_view;

  column_view.reorderable = false;
  column_view.show_row_separators = true;
  column_view.show_column_separators = true;
  column_view.append_column(key_column);
  column_view.append_column(value_column);

  key_column.expand = true;

  value_column.expand = true;
}

void on_setup_item(Object object) {
  var label = new Gtk.Label("");
  var list_item = object as Gtk.ListItem;

  label.halign = Gtk.Align.START;

  list_item?.set_child(label);
}