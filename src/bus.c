#include <pebble.h>
#include "bus.h"
#include "busdb.h"
#include "config.h"
#include "ventana_info.h"
#include "red.h"
  
  
Window* window;
// Barra de opciones
ActionBarLayer *action_bar;

// Capas del programa
static Layer *marcador;
TextLayer *textolinea_layer, *textoparada_layer, *dig1_layer, *dig2_layer, *dig3_layer, *linea_layer, *mensaje_layer;


// Variables de imágenes
GBitmap *arriba_bitmap, *abajo_bitmap, *pulsar_bitmap, *play_bitmap, *buscar_bitmap;



// Resto de variables
char texto[1024], tiempo1[100], tiempo2[100], tiempo_retorno[100];
static int numero1, numero2, numero3, posicion=0, cargando=0, i_buscar;

// Asignación para recibir datos
enum {
  KEY_LINEA_A_TIEMPO1 = 0,
  KEY_LINEA_A_TIEMPO2 = 1,
  KEY_LINEA_B_TIEMPO1 = 2,
  KEY_LINEA_B_TIEMPO2 = 3,
  KEY_LINEA_C_TIEMPO1 = 4,
  KEY_LINEA_C_TIEMPO2 = 5,
  KEY_LINEA_D_TIEMPO1 = 6,
  KEY_LINEA_D_TIEMPO2 = 7,
  KEY_LINEA_E_TIEMPO1 = 8,
  KEY_LINEA_E_TIEMPO2 = 9,
  KEY_LINEA_F_TIEMPO1 = 10,
  KEY_LINEA_F_TIEMPO2 = 11,
  KEY_LINEA_G_TIEMPO1 = 12,
  KEY_LINEA_G_TIEMPO2 = 13,
  KEY_LINEA_H_TIEMPO1 = 14,
  KEY_LINEA_H_TIEMPO2 = 15,
  KEY_LINEA_I_TIEMPO1 = 16,
  KEY_LINEA_I_TIEMPO2 = 17,
  KEY_LINEA_J_TIEMPO1 = 18,
  KEY_LINEA_J_TIEMPO2 = 19,
  KEY_LINEA_K_TIEMPO1 = 20,
  KEY_LINEA_K_TIEMPO2 = 21,
  KEY_LINEA_L_TIEMPO1 = 22,
  KEY_LINEA_L_TIEMPO2 = 23,
  KEY_LINEA_R1_TIEMPO1 = 24,
  KEY_LINEA_R1_TIEMPO2 = 25,
  KEY_LINEA_R2_TIEMPO1 = 26,
  KEY_LINEA_R2_TIEMPO2 = 27,
	KEY_PARADAS = 31,
	KEY_LINEAS = 32,
  KEY_TIPO = 30
};

char* subString (const char* input, int offset, int len, char* dest)
{
  
  int input_len = strlen (input);
  char es_cero[2];
  memset(&es_cero[0], 0, sizeof(es_cero));

  if (offset + len > input_len)
  {
     return NULL;
  }
  strncpy (es_cero, input+ offset, 1);

  if (strcmp(es_cero, "0") == 0) {
      len= 1;
      offset = offset+1;
  }
  strncpy (dest, input + offset, len);
  return dest;
}

int numero_parada()
  {
  // Aquí se debe comprabar si la parada existe
  int valor=(numero1*100)+(numero2*10)+numero3;
  return valor;
}

void pinta_datos(void)
{

  static char buffer1[]="12",buffer2[]="12",buffer3[]="12";

  snprintf(buffer1, sizeof(buffer1), "%d", numero1);
	text_layer_set_text(dig1_layer, buffer1);
  snprintf(buffer2, sizeof(buffer2), "%d", numero2);
	text_layer_set_text(dig2_layer, buffer2);
  snprintf(buffer3, sizeof(buffer3), "%d", numero3);
	text_layer_set_text(dig3_layer, buffer3);

  
}

void pinta_nombredeparada()
  {
   //APP_LOG(APP_LOG_LEVEL_DEBUG, "Parada: %i y total es %i.", numero_parada(), total_paradas);
  
    text_layer_set_text(mensaje_layer, devuelve_datos_parada(numero_parada(),0));


}






static void in_received_handler(DictionaryIterator *iter, void *context) 
{
  (void) context;	
  Tuple *t_tipo = dict_find(iter, KEY_TIPO);

  if (t_tipo->value->uint32 == 1)
    {  
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Recibo parada: %s", tiempo_retorno);


    posicion=0;
    cargando = 0;
    numero1= atoi(tiempo_retorno)/100;
    numero2= (atoi(tiempo_retorno) % 100) /10;
    numero3=(atoi(tiempo_retorno) % 10);
    layer_mark_dirty(marcador);
    pinta_datos();
    pinta_nombredeparada();

  }
  else
  {  
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Acabo de recibir datos (pebble). Retorno: %s", tiempo_retorno);
    for (int v=0;v<13;v++)
      {
        Tuple *t_tiempo1 = dict_find(iter, v*2);
        Tuple *t_tiempo2 = dict_find(iter, (v*2)+1);

        valores_parada[v].tiempo1 = t_tiempo1->value->uint32;
        valores_parada[v].tiempo2 = t_tiempo2->value->uint32;
      }
      posicion=0;
      layer_mark_dirty(marcador);
      action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);
      cargando = 0;
      vibes_short_pulse();
      //dialog_message_window_push(numero_parada(), devuelve_lineasxparada(numero_parada()));
      dialog_message_window_push(numero_parada(), texto, 4);
      pinta_nombredeparada();
      action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);
    }
  }


void manda_js(int tipo,int16_t parada)
{
	DictionaryIterator *iter;
 	app_message_outbox_begin(&iter);
  if (tipo==0)
  {
    dict_write_int16(iter, KEY_TIPO, 0);    
    dict_write_int16(iter, KEY_PARADAS, parada);
    dict_write_cstring(iter, KEY_LINEAS, devuelve_datos_parada(parada,1));
  }
  else if (tipo==1)
  {
    dict_write_int16(iter, KEY_TIPO, 1);    
            APP_LOG(APP_LOG_LEVEL_DEBUG, "Tipo 1");

  }
  dict_write_end(iter);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Mando mensaje");

 	app_message_outbox_send();

}

void busca_localizacion()
  {
      text_layer_set_text(mensaje_layer, "Buscando...");
      cargando = 1;
      //Borro la variable de tiempo 1 y 2 antes de volver a pedir datos.
      manda_js(1,0);
          //APP_LOG(APP_LOG_LEVEL_DEBUG, "En Pebble mando a buscar");

}

void envia_peticion()
  {
      text_layer_set_text(mensaje_layer, "Cargando...");
      cargando = 1;
      //Borro la variable de tiempo 1 y 2 antes de volver a pedir datos.
      memset(&tiempo1[0], 0, sizeof(tiempo1));
      memset(&tiempo2[0], 0, sizeof(tiempo2));
      manda_js(0,numero_parada());


}










void up_click_handler(ClickRecognizerRef recognizer, void *context) 
{
   if (cargando==1) return;
   switch(posicion) 
    {
		case 0:
      numero1==9 ? numero1=0 : numero1++;
      break;
		case 1:
      numero2==9 ? numero2=0 : numero2++;
      break;
		case 2:
      numero3==9 ? numero3=0 : numero3++;
      break;  
    }
  pinta_nombredeparada();
  pinta_datos();
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  if (cargando==1) return;

  switch(posicion) 
    {
		case 0:
      numero1==0 ? numero1=9 : numero1--;
      break;
		case 1:
      numero2==0 ? numero2=9 : numero2--;
      break;
		case 2:
      numero3==0 ? numero3=9 : numero3--;
      break;   
    }
  pinta_nombredeparada();
  pinta_datos();
}

void select_click_handler(ClickRecognizerRef recognizer, void *context)
{

  if (cargando==1)
    return;
  
  switch(posicion) 
    {
		case 0:
      posicion=1;
      break;
		case 1:
      posicion=2;
      action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, buscar_bitmap);

			break;
		case 2:
      if (strcmp(devuelve_datos_parada(numero_parada(),0),"Parada inexistente")==0)
      {
        posicion =0;
      }
    else
      {
        envia_peticion();
      }
      break;    
    
    }

  layer_mark_dirty(marcador);
}


void select_long_click_handler(ClickRecognizerRef recognizer, void *context)
{
  persist_write_int(FAV5_PKEY, persist_read_int(FAV4_PKEY));
  persist_write_int(FAV4_PKEY, persist_read_int(FAV3_PKEY));
  persist_write_int(FAV3_PKEY, persist_read_int(FAV2_PKEY));
  persist_write_int(FAV2_PKEY, persist_read_int(FAV1_PKEY));
  persist_write_int(FAV1_PKEY, (numero1*100) + (numero2*10) + (numero3));

  text_layer_set_text(mensaje_layer, "Parada agregada a favoritos.");

}

void marcador_update_callback(Layer *me, GContext* ctx) 
{

  // Color del fondo y color del trazo
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);

	switch(posicion) 
    {
		case 0:
      graphics_fill_rect(ctx, GRect(10, 85, 30, 3), 0, GCornerNone);  
      break;
		case 1:
      graphics_fill_rect(ctx, GRect(40, 85, 30, 3), 0, GCornerNone);    
			break;
		case 2:
      graphics_fill_rect(ctx, GRect(70, 85, 30, 3), 0, GCornerNone);  
			break;      
    }
} 


void click_config_provider(void *context) 
{
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 2000, select_long_click_handler, NULL);
}


static TextLayer* init_text_layer(GRect location, GColor colour, GColor background, const char *res_id, GTextAlignment alignment)
{
	TextLayer *layer = text_layer_create(location);
	text_layer_set_text_color(layer, colour);
	text_layer_set_background_color(layer, background);
	text_layer_set_font(layer, fonts_get_system_font(res_id));
  text_layer_set_overflow_mode(layer, GTextOverflowModeWordWrap);
	text_layer_set_text_alignment(layer, alignment);
	return layer;
}


void window_load(Window *window)
{
  //Capa para mostrar el marcador bajo los números
  marcador = layer_create(layer_get_bounds(window_get_root_layer(window)));
  layer_set_update_proc(marcador, marcador_update_callback); 
  layer_add_child(window_get_root_layer(window), marcador); 
  //Barra de opciones de la derecha
  action_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(action_bar, window);
  action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
  //Asignación de recursos gráficos
  #ifdef PBL_COLOR 
    arriba_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICONO_ARRIBA_BLACK);
    abajo_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_ABAJO_BLACK);
    pulsar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_PULSAR_BLACK);
    play_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_PLAY_BLACK);
    buscar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_BUSCAR_BLACK);
  #else
    arriba_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICONO_ARRIBA_WHITE);
    abajo_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_ABAJO_WHITE);
    pulsar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_PULSAR_WHITE);
    play_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_PLAY_WHITE);
    buscar_bitmap =  gbitmap_create_with_resource(RESOURCE_ID_ICONO_BUSCAR_WHITE);
  #endif
  //Asignación de iconos a la barra de opciones
  action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, arriba_bitmap );
  action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, abajo_bitmap);
  if (posicion==2)
    action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, buscar_bitmap);
  else
    action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);

  //Capas principales del programa
  
  textoparada_layer = init_text_layer(GRect(5, 5, 120, 35), GColorBlack, GColorClear, FONT_KEY_GOTHIC_28_BOLD, GTextAlignmentLeft);
  text_layer_set_text(textoparada_layer, "Parada");
	layer_add_child(window_get_root_layer(window), (Layer*) textoparada_layer);

  mensaje_layer = init_text_layer(GRect(5, 90, 100, 80), GColorBlack, GColorClear, FONT_KEY_GOTHIC_24_BOLD, GTextAlignmentLeft);
	text_layer_set_text(mensaje_layer, "Introduce parada");
  layer_add_child(window_get_root_layer(window), (Layer*) mensaje_layer);
 
  dig1_layer = init_text_layer(GRect(10, 30, 30, 50), GColorBlack, GColorClear, FONT_KEY_ROBOTO_BOLD_SUBSET_49, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig1_layer);
  
  dig2_layer = init_text_layer(GRect(40, 30, 30, 50), GColorBlack, GColorClear, FONT_KEY_ROBOTO_BOLD_SUBSET_49, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig2_layer);
  
  dig3_layer = init_text_layer(GRect(70, 30, 30, 50), GColorBlack, GColorClear, FONT_KEY_ROBOTO_BOLD_SUBSET_49, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) dig3_layer);
  
  pinta_datos();
  pinta_nombredeparada();
  if (i_buscar==1)
      busca_localizacion();
  if (posicion==2)
    {
    envia_peticion();
  }
  
}

void window_unload(Window *window)
{
  int t_parada = (numero1*100) + (numero2*10) + (numero3);
  if ((t_parada/100)>(total_paradas-1))
    t_parada=100;
  persist_write_int(PRINCIPAL_PKEY, t_parada);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Se guarda: %d + %d", (numero1*10000) + (numero2*1000) + (numero3*100), letra);

  posicion = 0;
  gbitmap_destroy(arriba_bitmap);
  gbitmap_destroy(abajo_bitmap);
  gbitmap_destroy(pulsar_bitmap);
  gbitmap_destroy(play_bitmap);
  gbitmap_destroy(buscar_bitmap);
  
  action_bar_layer_destroy(action_bar);

  text_layer_destroy(textoparada_layer);
  text_layer_destroy(dig1_layer);
  text_layer_destroy(dig2_layer);
	text_layer_destroy(dig3_layer);
  text_layer_destroy(mensaje_layer);
  layer_destroy(marcador);
   window_destroy(window);

}

/* Initialize the main app elements */
void carga_paradas(int n1, int fav, int buscar)
{
  i_buscar = 0;
  numero1= n1/100;
  numero2= (n1 % 100) /10;
  numero3=n1 % 10;
	window = window_create();
	WindowHandlers handlers = {
		.load = window_load,
		.unload = window_unload
	};
  #ifdef PBL_SDK_2
    window_set_fullscreen(window, true);
  #endif
	app_message_register_inbox_received(in_received_handler);					 
	window_set_window_handlers(window, (WindowHandlers) handlers);
  if (fav==1)
    posicion=2;
  if (buscar==1)
    i_buscar = 1;
  valores_parada[0].tiempo1 = 0;
	window_stack_push(window, true);


}

