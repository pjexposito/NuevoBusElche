var dict, dict_nuevo;
var i;
var numero_parada;
var tiempos;
var lineas_resueltas;
var lineas_utiles;
var valores_tiempo =[];

	var posiciones = [
[38.266147,-0.701039,1],
[38.267843,-0.702073,2],
[38.268081,-0.706858,3],
[38.269000,-0.709145,4],
[38.271950,-0.712123,5],
[38.273368,-0.713661,6],
[38.274833,-0.715297,7],
[38.278660,-0.717507,8],
[38.280412,-0.715856,9],
[38.283213,-0.713909,10],
[38.285575,-0.715387,11],
[38.284476,-0.720481,12],
[38.282739,-0.722450,13],
[38.281198,-0.720559,14],
[38.278436,-0.717563,15],
[38.275945,-0.715046,16],
[38.274736,-0.715895,17],
[38.271898,-0.715445,18],
[38.270801,-0.713699,19],
[38.268927,-0.711400,20],
[38.266794,-0.713399,21],
[38.265610,-0.710897,22],
[38.265455,-0.707096,23],
[38.265277,-0.703554,24],
[38.261510,-0.686106,25],
[38.259277,-0.683461,26],
[38.261579,-0.685050,27],
[38.257742,-0.690584,28],
[38.257584,-0.693101,29],
[38.257168,-0.696686,30],
[38.258276,-0.703122,31],
[38.258638,-0.704583,32],
[38.259077,-0.707670,33],
[38.259298,-0.710223,34],
[38.260699,-0.710870,35],
[38.262515,-0.710704,36],
[38.265502,-0.710440,37],
[38.266951,-0.711740,38],
[38.268362,-0.713869,39],
[38.269838,-0.716107,40],
[38.277361,-0.706800,41],
[38.274043,-0.712703,42],
[38.272635,-0.711190,43],
[38.271539,-0.709981,44],
[38.270462,-0.708789,45],
[38.268427,-0.707063,46],
[38.265280,-0.707401,47],
[38.262825,-0.707620,48],
[38.260071,-0.707822,49],
[38.258831,-0.706588,50],
[38.258210,-0.703429,51],
[38.256798,-0.696676,52],
[38.257037,-0.692774,53],
[38.257656,-0.690335,54],
[38.259896,-0.686982,55],
[38.269953,-0.703528,56],
[38.270794,-0.704146,57],
[38.261919,-0.737556,58],
[38.261857,-0.737157,59],
[38.271931,-0.706972,60],
[38.274460,-0.710035,61],
[38.276216,-0.711369,62],
[38.278468,-0.712741,63],
[38.279064,-0.710004,64],
[38.278175,-0.708342,65],
[38.275841,-0.706002,66],
[38.273833,-0.705164,67],
[38.272311,-0.704770,68],
[38.271562,-0.706982,69],
[38.268527,-0.706650,70],
[38.265562,-0.703367,71],
[38.262200,-0.685441,72],
[38.265253,-0.683551,73],
[38.267007,-0.685685,74],
[38.268626,-0.685954,75],
[38.270023,-0.682371,76],
[38.271712,-0.682991,77],
[38.271194,-0.685039,78],
[38.272391,-0.688169,79],
[38.272464,-0.694166,80],
[38.272040,-0.696451,81],
[38.272425,-0.701397,82],
[38.273612,-0.701703,83],
[38.275673,-0.703417,84],
[38.276289,-0.705451,85],
[38.275582,-0.707503,86],
[38.274512,-0.710389,87],
[38.269037,-0.706457,88],
[38.270750,-0.701883,89],
[38.271808,-0.696133,90],
[38.272551,-0.691278,91],
[38.273247,-0.687287,92],
[38.272633,-0.684487,93],
[38.271352,-0.683930,94],
[38.269731,-0.682631,95],
[38.267806,-0.681414,96],
[38.267229,-0.682791,97],
[38.265351,-0.683017,98],
[38.263459,-0.681696,99],
[38.262275,-0.685590,100],
[38.267339,-0.705315,101],
[38.265312,-0.698448,102],
[38.265722,-0.695456,103],
[38.262186,-0.696170,104],
[38.259267,-0.696676,105],
[38.263430,-0.681560,106],
[38.265549,-0.677084,107],
[38.265634,-0.677285,108],
[38.261273,-0.681865,109],
[38.262506,-0.687717,110],
[38.266426,-0.693665,111],
[38.268057,-0.693701,112],
[38.268053,-0.697594,113],
[38.268027,-0.705460,114],
[38.266057,-0.700575,115],
[38.268401,-0.696084,116],
[38.271375,-0.696534,117],
[38.267836,-0.680676,118],
[38.268102,-0.678608,119],
[38.271228,-0.679927,120],
[38.272402,-0.681443,121],
[38.271341,-0.696671,122],
[38.257667,-0.706522,123],
[38.254830,-0.706600,124],
[38.254737,-0.704586,125],
[38.275084,-0.716656,126],
[38.264133,-0.692990,127],
[38.259507,-0.712586,128],
[38.261062,-0.715175,129],
[38.262498,-0.714408,130],
[38.261495,-0.711535,131],
[38.262916,-0.708147,132],
[38.264301,-0.704805,133],
[38.264221,-0.703942,134],
[38.266807,-0.693351,135],
[38.268050,-0.688308,136],
[38.269687,-0.681734,137],
[38.269691,-0.678324,138],
[38.268748,-0.677094,139],
[38.269766,-0.672536,140],
[0,0],
[38.274339,-0.672352,142],
[38.275178,-0.676015,143],
[38.274114,-0.680064,144],
[38.270490,-0.679067,145],
[38.269721,-0.682130,146],
[38.269288,-0.683915,147],
[38.268870,-0.687386,148],
[38.268798,-0.693801,149],
[38.271898,-0.703932,150],
[38.273755,-0.704438,151],
[38.273401,-0.711174,152],
[0,0],
[38.280441,-0.730774,154],
[38.279188,-0.737776,155],
[38.279456,-0.739064,156],
[38.278149,-0.739937,157],
[38.277113,-0.738582,158],
[38.269357,-0.707612,159],
[38.271863,-0.717362,160],
[38.262381,-0.687789,161],
[38.264920,-0.679028,162],
[0,0],
[38.262231,-0.717837,164],
[38.265222,-0.718717,165],
[38.267744,-0.718198,166],
[38.267007,-0.722010,167],
[38.265092,-0.728280,168],
[38.263784,-0.731002,169],
[38.263876,-0.730651,170],
[38.262966,-0.733911,171],
[38.265071,-0.728142,172],
[38.266905,-0.721854,173],
[38.265836,-0.718780,174],
[38.264555,-0.718267,175],
[38.263159,-0.748628,176],
[38.267036,-0.710073,177],
[38.278683,-0.696562,178],
[38.281788,-0.697069,179],
[0,0],
[38.285848,-0.686114,183],
[0,0],
[38.284193,-0.689449,184],
[0,0],
[38.282215,-0.692423,185],
[38.281767,-0.695298,186],
[38.284822,-0.693950,187],
[38.285602,-0.691918,188],
[38.292175,-0.686208,189],
[38.296580,-0.684315,190],
[38.298583,-0.685341,191],
[38.300598,-0.685600,192],
[38.301934,-0.683450,193],
[38.300380,-0.681228,194],
[0,0],
[38.264961,-0.679272,196],
[38.264207,-0.674382,197],
[38.267702,-0.718390,198],
[0,0],
[38.266770,-0.673800,200],
[38.260750,-0.741862,201],
[38.261986,-0.743815,202],
[38.263103,-0.741006,203],
[38.262719,-0.734180,204],
[0,0],
[38.272271,-0.713776,206],
[38.275905,-0.714817,207],
[38.272150,-0.686452,208],
[38.270878,-0.715370,209],
[0,0],
[38.265015,-0.712298,212],
[0,0],
[38.277357,-0.706601,213],
[38.278811,-0.704441,214],
[38.278827,-0.704826,215],
[38.298290,-0.679164,216],
[38.299344,-0.676459,217],
[38.299017,-0.673601,218],
[38.293625,-0.675651,219],
[38.291034,-0.677244,220],
[38.288511,-0.680905,221],
[38.286934,-0.684080,222],
[38.281156,-0.696748,223],
[38.268862,-0.716865,224],
[0,0],
[38.278556,-0.737703,226],
[38.266892,-0.672554,227],
[38.265122,-0.675541,228],
[38.267582,-0.670129,229],
[38.267659,-0.670378,230],
[38.267017,-0.672526,231],
[38.276557,-0.676949,232],
[38.277418,-0.678095,233],
[0,0],
[38.270362,-0.679011,235],
[38.272956,-0.691245,236],
[38.267384,-0.677390,237],
[38.278003,-0.673974,238],
[38.278528,-0.670911,239],
[38.278299,-0.673438,240],
[38.276151,-0.679660,241],
[38.271925,-0.670579,242],
[38.257614,-0.703348,243],
[38.254950,-0.703535,244],
[38.255700,-0.707312,245],
[38.257787,-0.707122,246],
[38.262794,-0.703741,247],
[38.262294,-0.707195,248],
[38.262398,-0.711173,249],
[38.262658,-0.713843,250],
[38.260286,-0.718371,251],
[38.259321,-0.712311,252],
[38.259018,-0.708805,253],
[38.257598,-0.704357,254],
[38.259830,-0.704241,255],
[38.262043,-0.704064,256],
[38.252692,-0.703711,257],
[38.263360,-0.665778,258],
[38.262699,-0.662901,259],
[38.263644,-0.665594,260],
[38.264999,-0.664839,261],
[38.264368,-0.674361,262],
[0,0],
[38.262027,-0.683086,267],
[0,0],
[38.275687,-0.703663,268],
[0,0],
[38.273026,-0.701702,269],
[0,0],
[38.270445,-0.701515,270],
[38.268176,-0.701598,271],
[38.285720,-0.708979,272],
[38.289298,-0.713143,273],
[38.293550,-0.717696,274],
[38.293954,-0.721786,275],
[38.294816,-0.725382,276],
[38.295365,-0.728579,277],
[38.294732,-0.731719,278],
[38.293547,-0.731020,279],
[38.288991,-0.725616,280],
[38.287725,-0.721654,281],
[38.291245,-0.728923,282],
[38.289223,-0.713438,283],
[38.285751,-0.709153,284],
[38.256433,-0.697343,285],
[38.253210,-0.696567,286],
[38.254271,-0.693264,287],
[38.257002,-0.692385,288],
[38.273446,-0.738573,289],
[38.271959,-0.736714,290],
[38.267131,-0.729357,291],
[38.256469,-0.713923,292],
[38.255460,-0.714880,293],
[38.256639,-0.713846,294],
[0,0],
[38.274406,-0.682542,296],
[38.299197,-0.664515,297],
[38.305084,-0.665103,298],
[38.296440,-0.670865,299],
[38.279761,-0.695495,300],
[38.280569,-0.690748,301],
[38.282177,-0.685461,302],
[0,0],
[38.276868,-0.681284,304],
[38.264458,-0.712341,305],
[38.267192,-0.709312,306],
[38.277686,-0.714242,307],
[38.262263,-0.715321,308],
[38.258681,-0.713665,309],
[38.253250,-0.709634,310],
[38.264429,-0.707630,311],
[38.265877,-0.710736,312],
[38.270192,-0.703774,313],
[38.273741,-0.684472,314],
[38.274155,-0.682143,315],
[38.274627,-0.679137,316],
[38.274898,-0.675983,317],
[38.274442,-0.673873,318],
[38.271343,-0.670765,319],
[38.275088,-0.678284,320],
[38.273536,-0.687775,321],
[38.271055,-0.702261,322],
[38.270325,-0.704564,323],
[38.268837,-0.707741,324],
[38.267722,-0.718492,325],
[38.265828,-0.718869,326],
[0,0],
[38.268420,-0.697000,991],
[0,0],
[38.269920,-0.697420,992],
[0,0],
[38.266870,-0.696580,993],
[0,0],
[38.264210,-0.692950,994],
[0,0],
[38.260540,-0.693160,995]
	];

function distance(lat1, lon1, lat2, lon2) 
	{
		var radlat1 = Math.PI * lat1/180;
		var radlat2 = Math.PI * lat2/180;
		var theta = lon1-lon2;
		var radtheta = Math.PI * theta/180;
		var dist = Math.sin(radlat1) * Math.sin(radlat2) + Math.cos(radlat1) * Math.cos(radlat2) * Math.cos(radtheta);
		dist = Math.acos(dist);
		dist = dist * 180/Math.PI;
		dist = dist * 60 * 1.1515;
		dist = dist * 1.609344;
		return dist;
	}  


function localiza(){
 navigator.geolocation.watchPosition(showPosition, ErrorPosicion,{maximumAge:60000, timeout:15000});  
}


function ErrorPosicion()
	{
		//ParadaCercana(position.coords.latitude, position.coords.longitude);
		
    console.log("Error");	
	}    

function showPosition(position) 
	{
    console.log("LAT: "+position.coords.latitude+" .LONG: "+position.coords.longitude);
		ParadaCercana(position.coords.latitude, position.coords.longitude);		
	}    



// WUHUUUUU, funciona! Se incrementa notablemente la velocidad del programa
function BuscaParadas_soap(lineas, parada,linea) 
  {
    var t1, t2;

    if (linea=="1") linea="R";
    if (linea=="2") linea="R2";
    if (linea=="3") linea="R";
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.open('POST', 'http://www.isae-auesa.com:82/services/dinamica.asmx?op=GetPasoParada', true);

    // build SOAP request
    var sr =
        '<?xml version="1.0" encoding="utf-8"?>' +
        '<soapenv:Envelope ' + 
        'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" ' +
        'xmlns:api="http://127.0.0.1/Integrics/Enswitch/API" ' +
        'xmlns:xsd="http://www.w3.org/2001/XMLSchema" ' +
        'xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">' +
        '<soapenv:Body>' +
        '<GetPasoParada xmlns="http://tempuri.org/">' +
        '<linea>' + linea + '</linea>' +
        '<parada>' + parada + '</parada>' +
        '<status>0</status>' +
        '</GetPasoParada>' +
        '</soapenv:Body>' +
        '</soapenv:Envelope>';

    xmlhttp.timeout = 4000;
    xmlhttp.ontimeout = function () 
      { 
        console.log("Timed out!!!"); 
        t1 = "98";
        t2 = "98";
        comprueba_envio(linea, lineas, t1,t2);
      };
    
    xmlhttp.onreadystatechange = function () 
      {
      //console.log("Comprobando linea "+ linea);
      if (xmlhttp.readyState == 4) 
        {
        //console.log("Acabo de pasar el readystate 4");
        if (xmlhttp.status == 200) 
          {
            console.log("Ok, status 200.");
            console.log(typeof(xmlhttp.responseXML) == "undefined");

          if (typeof(xmlhttp.responseXML) == "undefined")
              {
              t1 = "95";
              t2 = "95";
              // No se puede ejecutar la búsqueda debido a "access-control-allow-origin". Hay que buscar una alternativa.
              }
          else if (xmlhttp.responseXML.getElementsByTagName("GetPasoParadaResult")[0].getElementsByTagName("PasoParada")[0])
            {
              t1 = xmlhttp.responseXML.getElementsByTagName("GetPasoParadaResult")[0].getElementsByTagName("PasoParada")[0].getElementsByTagName("e1")[0].getElementsByTagName("minutos")[0].textContent;
              t2 = xmlhttp.responseXML.getElementsByTagName("GetPasoParadaResult")[0].getElementsByTagName("PasoParada")[0].getElementsByTagName("e2")[0].getElementsByTagName("minutos")[0].textContent;
            }
          else
            {
              t1 = "98";
              t2 = "98";
            }
          comprueba_envio(linea, lineas, t1,t2);
          return true;
          }
        else
          {
            // No hay forma de recoger los datos. Sin conexión a Internet.
            t1 = "96";
            t2 = "96";
            comprueba_envio(linea, lineas, t1,t2); 
          }
        }
      };
      // Send the POST request
      xmlhttp.setRequestHeader('Content-Type', 'text/xml');
      xmlhttp.send(sr);
    }

function ParadaCercana(lat, long)
	{
    var global_menor;
    var menor=99999;
    var distancia_anterior = 99999;
    var distancia;
    for (var x = 0; x < posiciones.length; x++) 
		{ 
      distancia = distance(lat, long, posiciones[x][0], posiciones[x][1]);
      //console.log("Busco "+lat+", "+long+" frente a "+ posiciones[x][0]+" y "+ posiciones[x][1]);
      if (distancia_anterior>distancia) 
          {
          menor = x;
          distancia_anterior = distancia;
          numero_parada = posiciones[x][2];
          }
        //console.log('Para ' + x + ' es  ' + distancia + ". Anterior es :" + distancia_anterior + ". Menor vale: " + menor);
        }
        global_menor = menor;
        //console.log("El menor es la posición: " + menor);
        //console.log("La distancia es: " + distancia);
        //console.log("La parada es: " + numero_parada);
    console.log("La parada es "+numero_parada);
    dict = {"KEY_TIPO": 1, "KEY_PARADA_CERCANA" : Number(numero_parada)};
	Pebble.sendAppMessage(dict);
    
	}


function ResuelveParada(parada, lineas) {
    lineas_utiles = 0;
    
  for (i=0;i<13+1;i++)
      {
        valores_tiempo[i] = [];
        valores_tiempo[i][0] = 0;
        valores_tiempo[i][1] = 0;
      }
  
    for (i = 0; i < lineas.length; i++)
      if (lineas[i] != "0") 
        lineas_utiles = lineas_utiles + 1;
  
    console.log("Busco estas lineas: " + lineas + ". Hay " + lineas_utiles + " lineas útiles");

    for (i = 0; i < lineas.length; i++) { 
      if (lineas[i] != "0") 
        {
          console.log("Busco en soap la parada "+parada+" para la linea "+lineas[i]);
        BuscaParadas_soap(lineas, parada, lineas[i], i);
        }
    }     

}

function comprueba_envio(linea, lineas, tiempo1, tiempo2)
  {
    lineas_resueltas = lineas_resueltas + 1;
    var todas_lineas = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "R", "R2"];
    valores_tiempo[todas_lineas.indexOf(linea)][0] = tiempo1;
    valores_tiempo[todas_lineas.indexOf(linea)][1] = tiempo2;
    //console.log("Llevo procesadas "+lineas_resueltas+". El total son :" +lineas_utiles + "\nTiempos para linea " + linea + " vale: "+ tiempos_enviados);
    if (lineas_resueltas == lineas_utiles)
      {
        dict_nuevo = {
          "KEY_TIPO": 0,
          "KEY_LINEA_A_TIEMPO1": Number(valores_tiempo[0][0]), "KEY_LINEA_A_TIEMPO2": Number(valores_tiempo[0][1]),  
          "KEY_LINEA_B_TIEMPO1": Number(valores_tiempo[1][0]), "KEY_LINEA_B_TIEMPO2": Number(valores_tiempo[1][1]),  
          "KEY_LINEA_C_TIEMPO1": Number(valores_tiempo[2][0]), "KEY_LINEA_C_TIEMPO2": Number(valores_tiempo[2][1]),  
          "KEY_LINEA_D_TIEMPO1": Number(valores_tiempo[3][0]), "KEY_LINEA_D_TIEMPO2": Number(valores_tiempo[3][1]),  
          "KEY_LINEA_E_TIEMPO1": Number(valores_tiempo[4][0]), "KEY_LINEA_E_TIEMPO2": Number(valores_tiempo[4][1]),  
          "KEY_LINEA_F_TIEMPO1": Number(valores_tiempo[5][0]), "KEY_LINEA_F_TIEMPO2": Number(valores_tiempo[5][1]),  
          "KEY_LINEA_G_TIEMPO1": Number(valores_tiempo[6][0]), "KEY_LINEA_G_TIEMPO2": Number(valores_tiempo[6][1]),  
          "KEY_LINEA_H_TIEMPO1": Number(valores_tiempo[7][0]), "KEY_LINEA_H_TIEMPO2": Number(valores_tiempo[7][1]),  
          "KEY_LINEA_I_TIEMPO1": Number(valores_tiempo[8][0]), "KEY_LINEA_I_TIEMPO2": Number(valores_tiempo[8][1]),  
          "KEY_LINEA_J_TIEMPO1": Number(valores_tiempo[9][0]), "KEY_LINEA_J_TIEMPO2": Number(valores_tiempo[9][1]),  
          "KEY_LINEA_K_TIEMPO1": Number(valores_tiempo[10][0]), "KEY_LINEA_K_TIEMPO2": Number(valores_tiempo[10][1]),  
          "KEY_LINEA_L_TIEMPO1": Number(valores_tiempo[11][0]), "KEY_LINEA_L_TIEMPO2": Number(valores_tiempo[11][1]),  
          "KEY_LINEA_R1_TIEMPO1": Number(valores_tiempo[12][0]), "KEY_LINEA_R1_TIEMPO2": Number(valores_tiempo[12][1]),  
          "KEY_LINEA_R2_TIEMPO1": Number(valores_tiempo[13][0]), "KEY_LINEA_R2_TIEMPO2": Number(valores_tiempo[13][1])

         };
         
      //console.log("Mensaje enviados al pebble:" + dict_nuevo);
      console.log("Al final he sacado esto:" + valores_tiempo);
      Pebble.sendAppMessage(dict_nuevo);   
      }
  }


Pebble.addEventListener("ready",
  function(e) {
	//Se activa el reloj por primera vez. Se piden los datos por primera vez
  //console.log("Evento Ready");

  }
);



Pebble.addEventListener("appmessage",
  function(e) {
    //Se refresca la información
  var tipo = e.payload.KEY_TIPO;
  console.log("El tipo es "+tipo);
    
  if (tipo === 0)
  {
    var parada=e.payload.KEY_PARADAS;
    var lineas = e.payload.KEY_LINEAS.split('');
    lineas_resueltas = 0;
    tiempos = "";
    console.log("Mensaje recibido. Parada: " + parada + ". Lineas: " + lineas);
    ResuelveParada(parada, lineas);
  }
  else if (tipo==1)
  {
        //console.log("Busco cosas");

    localiza();
  }
  }
);