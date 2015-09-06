#include <pebble.h>
#include "ventana_info.h"
#include "config.h"
#include "red.h"

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
static TextLayer *capa_texto_para_scroll, *s_titulo_layer;
static ScrollLayer *capa_scroll;
Layer *window_layer;

static BitmapLayer *s_icon_layer, *s_fondo_layer;
int parada_global, i_total_lineas;
char i_lineas[400], string_parada[11], string_parada_total[30], string_parada_total2[15];

static GBitmap *s_icon_bitmap;


static void window_load(Window *window) {
  s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGEN_BUS_INV);
  s_fondo_layer = bitmap_layer_create(GRect(0, 0, 144, 40));
  bitmap_layer_set_background_color(s_fondo_layer, COLOR_CABECERA);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_fondo_layer));


  // CAPA SCROLL
  GRect bounds = layer_get_frame(window_layer);
  capa_scroll = scroll_layer_create(GRect(10, 10 + 28 + 5, 124, 168 - (10 + 28 + 10)));
  scroll_layer_set_click_config_onto_window(capa_scroll, window);
  capa_texto_para_scroll = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, 2000} });
  text_layer_set_font(capa_texto_para_scroll, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_color(capa_texto_para_scroll, COLOR_TEXTO_CUERPO);  
    scroll_layer_set_shadow_hidden(capa_scroll, true);

  text_layer_set_background_color(capa_texto_para_scroll, GColorClear);
  text_layer_set_text(capa_texto_para_scroll, "Cargando...");
  GSize content_size = GSize(120,30); // ESE 2000 es el importante. Indica si habrá o no scroll
  text_layer_set_size(capa_texto_para_scroll, content_size);
  scroll_layer_set_content_size(capa_scroll, GSize(140, content_size.h));
  scroll_layer_add_child(capa_scroll, text_layer_get_layer(capa_texto_para_scroll));
  layer_add_child(window_get_root_layer(window), scroll_layer_get_layer(capa_scroll)); 
  

  
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
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Termina de cargar la capa");
  //


      
}

void sacudida (AccelAxisType axis, int32_t direction) {
  scroll_layer_set_content_offset(capa_scroll, GPointZero, false);
  text_layer_set_text(capa_texto_para_scroll, "Solicitando nuevos datos...");
  layer_mark_dirty(window_layer);
  tiempo_parada(parada_global);
}

void pinta_texto()
  {
        vibes_short_pulse();

    memset(&i_lineas[0], 0, sizeof(i_lineas));
    int total_lineas = 0;
    //strcpy(i_lineas,"");

    for (int v=0;v<TOTAL_KEY_PARADAS+1;v++)
      {
        memset(&string_parada_total[0], 0, sizeof(string_parada_total));
        memset(&string_parada_total2[0], 0, sizeof(string_parada_total2));
        if (valores_parada[v].tiempo1==98)
          {
            total_lineas++;
            snprintf(string_parada_total, sizeof(string_parada_total), "Parada %c: Sin autobuses.\n", v+65);
            strcat(i_lineas, string_parada_total); 
          }   
        else if (valores_parada[v].tiempo1==95)
          {
            total_lineas++;
            snprintf(string_parada_total, sizeof(string_parada_total), "Error de servidor.\n");
            strcat(i_lineas, string_parada_total); 
          }       
        else if (valores_parada[v].tiempo1+valores_parada[v].tiempo2!=0)
          {
          total_lineas++;
          snprintf(string_parada_total, sizeof(string_parada_total), "Parada %c: %i", v+65, valores_parada[v].tiempo1);
          APP_LOG(APP_LOG_LEVEL_DEBUG, "Para parada %c, tiempo1 vale %i y tiempo2, vale %i", v+65, valores_parada[v].tiempo1, valores_parada[v].tiempo2);
          strcat(i_lineas, string_parada_total);
          if (valores_parada[v].tiempo2>0)
            {
            snprintf(string_parada_total2, sizeof(string_parada_total2), " y %i", valores_parada[v].tiempo2);
            strcat(i_lineas, string_parada_total2);
            APP_LOG(APP_LOG_LEVEL_DEBUG, "Añado %s", string_parada_total2);
            }
            strcat(i_lineas, " minutos.\n");
          }

      }
  
  if (total_lineas> 3)
    text_layer_set_font(capa_texto_para_scroll, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  else
    text_layer_set_font(capa_texto_para_scroll, fonts_get_system_font(FONT_KEY_GOTHIC_28));

        text_layer_set_text(capa_texto_para_scroll, i_lineas);
  GSize content_size = GSize(115,50*total_lineas); // 
  text_layer_set_size(capa_texto_para_scroll, GSize(130, content_size.h + 14));
  scroll_layer_set_content_size(capa_scroll, GSize(130, content_size.h));
  layer_mark_dirty(window_layer);

}

static void window_unload(Window *window) {
  text_layer_destroy(capa_texto_para_scroll);
  text_layer_destroy(s_titulo_layer);

  bitmap_layer_destroy(s_icon_layer);
  gbitmap_destroy(s_icon_bitmap);
  accel_tap_service_unsubscribe();

  window_destroy(window);
  s_main_window = NULL;
}

void dialog_message_window_push(int parada) {
  if(!s_main_window) {
    parada_global = parada;
    tiempo_parada(parada_global);
    snprintf(string_parada, sizeof(string_parada), "Parada %d", parada);

    s_main_window = window_create();
    window_layer = window_get_root_layer(s_main_window);
    accel_tap_service_subscribe (sacudida);
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

