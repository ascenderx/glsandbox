Utilities.prototype.__interval__ = 0;
Utilities.prototype.__tickFunc__ = null;
Utilities.prototype.__paused__ = false;

Utilities.prototype.setTickFunc = function(func) {
    this.__tickFunc__ = func;
};

Utilities.prototype.setFramerate = function(framerate) {
    this.__interval__ = 1000/framerate;
};

Utilities.prototype.setTickInterval = function(interval) {
    this.__interval__ = interval;
};

Utilities.prototype.isPaused = function() {
    return this.__paused__;
};

Utilities.prototype.pause = function() {
    this.__paused__ = true;
};

Utilities.prototype.resume = function() {
    this.__paused__ = false;
};

Utilities.prototype.togglePause = function() {
    this.__paused__ = !this.__paused__;
};

Utilities.prototype.run = function() {
    if (!this.__tickFunc__) {
        return;
    }
    
    let util = this;
    this.__window__.setInterval(function() {
        if (!util.__paused__) {
            util.__tickFunc__(util);
        }
    }, this.__interval__);
};