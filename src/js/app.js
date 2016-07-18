var Clay = require('pebble-clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);



/*var pebbleToken = "882Y";

Pebble.addEventListener('ready', function (e) {
    var settings = localStorage.getItem(pebbleToken);
    if (typeof(settings) == 'string') {
      try {
        console.log('settings found: ' + settings);
        Pebble.sendAppMessage(JSON.parse(settings));
      }
      catch (ex) { console.log('error encountered: ' + ex); }
    }
    else { console.log('could not find settings.'); }

    var request = new XMLHttpRequest();
    request.open('GET', 'http://x.setpebble.com/api/' + pebbleToken + '/' + Pebble.getAccountToken(), true);
    request.onload = function (e) {
      try {
        Pebble.sendAppMessage(JSON.parse(request.responseText));
      }
      catch (ex) { console.log('error encountered: ' + ex); }
    };
    request.send(null);  
});

Pebble.addEventListener('showConfiguration', function (e) {
  Pebble.openURL('http://x.setpebble.com/' + pebbleToken + '/' + Pebble.getAccountToken());
});

Pebble.addEventListener('webviewclosed', function (e) {
  if ((typeof(e.response) == 'string') && (e.response.length > 0)) {
    try {
      Pebble.sendAppMessage(JSON.parse(e.response));
      localStorage.setItem(pebbleToken, e.response);
    }
      catch (ex) { console.log('error encountered: ' + ex); }
  }
});*/
