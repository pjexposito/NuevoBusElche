#include <pebble.h>
#include "red.h"
#include "config.h"
#include "busdb.h"
#include "ventana_info.h"

static void appmsg_in_received(DictionaryIterator *received, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "In received.");

  (void) context;	

      for (int v=0;v<TOTAL_KEY_PARADAS+1;v++)
      {
        Tuple *t_tiempo1 = dict_find(received, v*2);
        Tuple *t_tiempo2 = dict_find(received, (v*2)+1);

        valores_parada[v].tiempo1 = t_tiempo1->value->int8;
        valores_parada[v].tiempo2 = t_tiempo2->value->int8;
      }
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Terminado.");
   pinta_texto();

      for (int v=0;v<TOTAL_KEY_PARADAS+1;v++)
        {
            APP_LOG(APP_LOG_LEVEL_DEBUG, "En parada %i, t1 es %i y t2 es %i", v, valores_parada[v].tiempo1, valores_parada[v].tiempo2);

      }


}

static void appmsg_in_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "In dropped: %i", reason);
  // Request a new update...
  //request_weather();
}

static void appmsg_out_sent(DictionaryIterator *sent, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Out sent.");
}


void init_network()
{
  app_message_register_inbox_received(appmsg_in_received);
  app_message_register_inbox_dropped(appmsg_in_dropped);
  app_message_register_outbox_sent(appmsg_out_sent);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());		



}

void close_network()
{
  app_message_deregister_callbacks();
}

void request_weather()
{
  int parada = 177;
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
    dict_write_int16(iter, KEY_TIPO, 0);    
    dict_write_int16(iter, KEY_PARADAS, parada);
    dict_write_cstring(iter, KEY_LINEAS, devuelve_datos_parada(parada,1));

  app_message_outbox_send();
}
