Utilities.prototype.__mouse__ = {
    x: null,
    y: null,
    buttons: 0,
};

Utilities.prototype.__mouseMoveCallback__ = function(event) {
    
};

Utilities.prototype.__mouseOverCallback__ = function(event) {
    
};

Utilities.prototype.__mouseOutCallback__ = function(event) {
    
};

Utilities.prototype.__mouseDownCallback__ = function(event) {
    
};

Utilities.prototype.__mouseUpCallback__ = function(event) {
    
};

Utilities.prototype.__mouseDblClickCallback__ = function(event) {
    
};

Utilities.prototype.__keyDownCallback__ = function(event) {
    
};

Utilities.prototype.__keyUpCallback__ = function(event) {
    
};

Utilities.prototype.__touchStartCallback__ = function(event) {
    
};

Utilities.prototype.__touchEndCallback__ = function(event) {
    
};

Utilities.prototype.__touchCancelCallback__ = function(event) {
    
};

Utilities.prototype.__touchMoveCallback__ = function(event) {
    
};

Utilities.prototype.__gamepadConnectedCallback__ = function(event) {
    
};

Utilities.prototype.__gamepadDisconnectedCallback__ = function(event) {

};

Utilities.prototype.initInputHandlers = function() {
    this.__window__.addEventListener('mousemove', this.__mouseMoveCallback__);
    this.__window__.addEventListener('mouseover', this.__mouseOverCallback__);
    this.__window__.addEventListener('mouseout', this.__mouseOutCallback__);
    this.__window__.addEventListener('mousedown', this.__mouseDownCallback__);
    this.__window__.addEventListener('mouseup', this.__mouseUpCallback__);
    this.__window__.addEventListener('dblclick', this.__mouseDblClickCallback__);
    this.__window__.addEventListener('keydown', this.__keyDownCallback__);
    this.__window__.addEventListener('keyup', this.__keyUpCallback__);
    this.__window__.addEventListener('touchstart', this.__touchStartCallback__);
    this.__window__.addEventListener('touchend', this.__touchEndCallback__);
    this.__window__.addEventListener('touchcancel', this.__touchCancelCallback__);
    this.__window__.addEventListener('touchmove', this.__touchMoveCallback__);
    this.__window__.addEventListener('gamepadconnected', this.__gamepadConnectedCallback__);
    this.__window__.addEventListener('gamepaddisconnected', this.__gamepadDisconnectedCallback__);
};