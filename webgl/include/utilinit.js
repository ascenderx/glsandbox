Utilities.prototype.__interval__ = 0;
Utilities.prototype.__tickFunc__ = null;

Utilities.prototype.setTickFunc = function(func) {
    this.__tickFunc__ = func;
};

Utilities.prototype.setFramerate = function(framerate) {
    this.__interval__ = 1000/framerate;
};

Utilities.prototype.setTickInterval = function(interval) {
    this.__interval__ = interval;
};

Utilities.prototype.run = function() {
    if (!this.__tickFunc__) {
        return;
    }
    
    this.window.setInterval(this.__tickFunc__, this.__interval__);
};