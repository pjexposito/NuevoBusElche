#include <pebble.h>
#include "ventana_info.h"
#include "config.h"

#ifdef PBL_COLOR 
#  define COLOR_CABECERA GColorBlack
#  define COLOR_TEXTO_CABECERA GColorWhite
#  define COLOR_TEXTO_CUERPO GColorBlack
#  define COLOR_CUERPO GColorMintGreen
#else
#  define COLOR_CABECERA GColorBlack
#  define COLOR_TEXTO_CABECERA GColorWhite
#  define COLOR_TEXTO_CUERPO GColorBlack
#  define COLOR_CUERPO GColorWhite
#endif
  
  
static Window *s_main_window;
static TextLayer *s_label_layer, *s_titulo_layer;
static ScrollLayer *s_scroll_layer;

static BitmapLayer *s_icon_layer, *s_fondo_layer;
int i_parada, i_total_lineas;
char i_lineas[300], string_parada[11], string_parada_total[30], string_parada_total2[15];

static GBitmap *s_icon_bitmap;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGEN_BUS_INV);
  s_fondo_layer = bitmap_layer_create(GRect(0, 0, 144, 40));
  bitmap_layer_set_background_color(s_fondo_layer, COLOR_CABECERA);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_fondo_layer));



  s_scroll_layer = scroll_layer_create(GRect(10, 10 + 28 + 5, 124, 168 - (10 + 28 + 10)));
  scroll_layer_set_click_config_onto_window(s_scroll_layer, window);
  GRect bounds = layer_get_frame(window_layer);
  GRect max_text_bounds = GRect(0, 0, 120, 2000);
  s_label_layer = text_layer_create(max_text_bounds);
  text_layer_set_text(s_label_layer, i_lineas);
  text_layer_set_text_color(s_label_layer, COLOR_TEXTO_CUERPO);  
  text_layer_set_background_color(s_label_layer, GColorClear);
  if (i_total_lineas> 3)
    text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  else
    text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
    
  //layer_add_child(window_layer, text_layer_get_layer(s_label_layer));
  
  
  
    // Trim text layer and scroll content to fit text box
  GSize max_size = text_layer_get_content_size(s_label_layer);
  text_layer_set_size(s_label_layer, max_size);
  scroll_layer_set_content_size(s_scroll_layer, GSize(bounds.size.w, max_size.h + 4));
  scroll_layer_set_shadow_hidden(s_scroll_layer, true);
  scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(s_label_layer));
  layer_add_child(window_layer, scroll_layer_get_layer(s_scroll_layer));

  // CAPA DE LA PARADA
  s_titulo_layer = text_layer_create(GRect(38, 0 , 101, 40));
  text_layer_set_text(s_titulo_layer, string_parada);
  text_layer_set_background_color(s_titulo_layer, GColorClear );
  text_layer_set_text_color(s_titulo_layer, COLOR_TEXTO_CABECERA );
  text_layer_set_text_alignment(s_titulo_layer, GTextAlignmentCenter);
  text_layer_set_font(s_titulo_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(s_titulo_layer));
  // FIN DE CAPA DE LA PARADA
  
  // CAPA DEL ICONO DEL BUS
  s_icon_layer = bitmap_layer_create(GRect(5, 5, 28, 28));
  bitmap_layer_set_bitmap(s_icon_layer, s_icon_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));
  // FIN DE LA CAPA
  

      
}

static void window_unload(Window *window) {
  text_layer_destroy(s_label_layer);
  text_layer_destroy(s_titulo_layer);

  bitmap_layer_destroy(s_icon_layer);
  gbitmap_destroy(s_icon_bitmap);

  window_destroy(window);
  s_main_window = NULL;
}

void dialog_message_window_push(int parada, char lineas[200], int total_lineas) {
  if(!s_main_window) {
    i_parada = parada;
    i_total_lineas = total_lineas;
    memset(&i_lineas[0], 0, sizeof(i_lineas));
    memset(&string_parada[0], 0, sizeof(string_parada));

    for (int v=0;v<TOTAL_KEY_PARADAS+1;v++)
      {
        if ((valores_parada[v].tiempo1==98) && (valores_parada[v].tiempo2==98))
          {
            memset(&string_parada_total[0], 0, sizeof(string_parada_total));
            snprintf(string_parada_total, sizeof(string_parada_total), "Parada %c: Sin autobuses.\n", v+65);
            strcat(i_lineas, string_parada_total); 
          }        
        else if ((valores_parada[v].tiempo1!=0) && (valores_parada[v].tiempo2!=0))
          {
          memset(&string_parada_total[0], 0, sizeof(string_parada_total));
          snprintf(string_parada_total, sizeof(string_parada_total), "Parada %c: %i", v+65, valores_parada[v].tiempo1);
          //APP_LOG(APP_LOG_LEVEL_DEBUG, "Para parada %c, tiempo1 vale %i y tiempo2, vale %i", v+65, valores_parada[v].tiempo1, valores_parada[v].tiempo2);
          strcat(i_lineas, string_parada_total);
          if (valores_parada[v].tiempo2>0)
            {
            memset(&string_parada_total2[0], 0, sizeof(string_parada_total2));
            snprintf(string_parada_total2, sizeof(string_parada_total2), " y %i", valores_parada[v].tiempo2);
            strcat(i_lineas, string_parada_total2);
            APP_LOG(APP_LOG_LEVEL_DEBUG, "Añado %s", string_parada_total2);
            }
            strcat(i_lineas, "\n");
          }

      }
    //strcat(i_lineas, lineas);
    snprintf(string_parada, sizeof(string_parada), "Parada %d", parada);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Total: %s", i_lineas);

    s_main_window = window_create();
    window_set_background_color(s_main_window, COLOR_CUERPO);
    #ifdef PBL_SDK_2
      window_set_fullscreen(s_main_window, true);
    #endif
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
  }
  window_stack_push(s_main_window, true);
}

