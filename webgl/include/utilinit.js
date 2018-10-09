Utilities.prototype.__interval__ = 0;
Utilities.prototype.__tickFunc__ = null;
Utilities.prototype.__paused__ = false;
Utilities.prototype.__prevTime__ = null;

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

Utilities.prototype.__tick__ = function(timestamp) {
    if (!this.__prevTime__) {
        this.__prevTime__ = timestamp;
    }
    
    
    let progress = timestamp - this.__prevTime__;
    if (progress > this.__interval__) {
        this.__tickFunc__(this);
        this.__prevTime__ = timestamp;
    }
    
    this.__window__.requestAnimationFrame(this.__tick__.bind(this));
};

Utilities.prototype.run = function(timestamp) {
    if (!this.__tickFunc__) {
        return;
    }
    
    this.__window__.requestAnimationFrame(this.__tick__.bind(this));
};