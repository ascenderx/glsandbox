Utilities.prototype.__sounds__ = {};

Utilities.prototype.addAudio = function(name, path) {
    this.__sounds__[name] = {
        data: new Audio(path),
        muting: true,
    };
};

Utilities.prototype.setAudioMuteOnPause = function(name, muting) {
    if (!(name in this.__sounds__)) {
        return;
    }
    
    this.__sounds__[name].muting = muting;
};

Utilities.prototype.hasAudio = function(name) {
    return name in this.__sounds__;
};

Utilities.prototype.playAudio = function(name) {
    if (!(name in this.__sounds__)) {
        return;
    }
    
    let sound = this.__sounds__[name];
    if (!this.__paused__ || !sound.muting) {
        sound.data.currentTime = 0;
        sound.data.play();
    }
};