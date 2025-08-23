#ifndef __LIST_VIEW_H__
#define __LIST_VIEW_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define APP_ID "io.github.Miqueas.GTK-Examples.C.Gtk4.ListView"
#define APP_NAME "GtkListView"

#define MGE_TYPE_ITEM (mge_item_get_type())
#define MGE_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MGE_TYPE_ITEM, MgeItem))
#define MGE_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), MGE_TYPE_ITEM, MgeItemClass))
#define MGE_IS_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MGE_TYPE_ITEM))
#define MGE_IS_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), MGE_TYPE_ITEM))
#define MGE_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), MGE_TYPE_ITEM, MgeItemClass))

typedef struct _MgeItem MgeItem;
typedef struct _MgeItemClass MgeItemClass;

struct _MgeItem {
  GObject parent_instance;
  gchar* key;
  gchar* value;
};

struct _MgeItemClass {
  GObjectClass parent_class;
};


GType mge_item_get_type(void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC(MgeItem, g_object_unref)
MgeItem* mge_item_new(const gchar* key, const gchar* value);

G_END_DECLS

#endif // __LIST_VIEW_H__