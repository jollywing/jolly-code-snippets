
/**
 * ukey.js
 * 用于ukey登录认证的javascript变量与函数
 * jiqing.wu@cs2c.com.cn, 2016-08-17 Wed
 */

function UKEY_checkPlugin()
{
    var mimetype = navigator.mimeTypes["application/mozilla-npruntime-scriptable-plugin"];
    if (mimetype == null)
        return false;
    var plugin = mimetype.enabledPlugin;

    if (plugin) {
        return true;
    }
    return false;
}


function UKEY_checkAvailable() {
    var ukeyObj = document.getElementById('ukey-embed');
    console.log(ukeyObj == null);
    ukeyObj.UkeyInit();
    var result = ukeyObj.UkeyCheckAvailable("1234");
    ukeyObj.UkeyFinish();
    if (result == 1)
        return true;
    else
        return false;
}

function UKEY_getMessage() {
    if (!UKEY_pluginAvailable) {
        return "";
    }
    var ukeyObj = document.getElementById('ukey-embed');
    ukeyObj.UkeyInit();
    var message = ukeyObj.UkeyGenerateRequestPacket();
    ukeyObj.UkeyFinish();
    return message;
}
