const MOUSE_LEFT = 0;
const MOUSE_MIDDLE = 1;
const MOUSE_RIGHT = 2;

Utilities.prototype.__mouse__ = {
    x: null,
    y: null,
    xWin: null,
    yWin: null,
    xAbs: null,
    yAbs: null,
    buttons: [false, false, false],
};

Utilities.prototype.__keys__ = {};

Utilities.prototype.__mouseAdjustPos__ = function(event) {
    this.__mouse__.x = event.clientX - this.__mouse__.offsetX;
    this.__mouse__.y = event.clientY - this.__mouse__.offsetY;
    this.__mouse__.xWin = event.clientX;
    this.__mouse__.yWin = event.clientY;
    this.__mouse__.xAbs = event.screenX;
    this.__mouse__.yAbs = event.screenY;
};

Utilities.prototype.__mouseMoveCallback__ = function(event) {
    this.__mouseAdjustPos__(event);
};

Utilities.prototype.__mouseOverCallback__ = function(event) {
    this.__mouseAdjustPos__(event);
};

Utilities.prototype.__mouseOutCallback__ = function(event) {
    this.__mouse__.x = 0;
    this.__mouse__.y = 0;
};

Utilities.prototype.__mouseDownCallback__ = function(event) {
    this.__mouseAdjustPos__(event);
    let btn = event.button;
    if (btn < 0 || btn > 2) {
        return;
    }
    this.__mouse__.buttons[btn] = true;
};

Utilities.prototype.__mouseUpCallback__ = function(event) {
    this.__mouseAdjustPos__(event);
    let btn = event.button;
    if (btn < 0 || btn > 2) {
        return;
    }
    this.__mouse__.buttons[btn] = false;
};

Utilities.prototype.__mouseDblClickCallback__ = function(event) {
    this.__window__.preventDefault();
};

Utilities.prototype.__keyDownCallback__ = function(event) {
    let key = event.key;
    if (!(key in this.__keys__)) {
        this.__keys__[key] = {
            count: 0,
            debounced: false,
        };
    }
    this.__keys__[key].count++;
};

Utilities.prototype.__keyUpCallback__ = function(event) {
    let key = event.key;
    if (!(key in this.__keys__)) {
        return;
    }
    delete this.__keys__[key];
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
    this.__window__.addEventListener('mousemove', this.__mouseMoveCallback__.bind(this));
    this.__window__.addEventListener('mouseover', this.__mouseOverCallback__.bind(this));
    this.__window__.addEventListener('mouseout', this.__mouseOutCallback__.bind(this));
    this.__window__.addEventListener('mousedown', this.__mouseDownCallback__.bind(this));
    this.__window__.addEventListener('mouseenter', this.__mouseOverCallback__.bind(this));
    this.__window__.addEventListener('mouseleave', this.__mouseOutCallback__.bind(this));
    this.__window__.addEventListener('mouseup', this.__mouseUpCallback__.bind(this));
    this.__window__.addEventListener('dblclick', this.__mouseDblClickCallback__.bind(this));
    this.__window__.addEventListener('keydown', this.__keyDownCallback__.bind(this));
    this.__window__.addEventListener('keyup', this.__keyUpCallback__.bind(this));
    this.__window__.addEventListener('touchstart', this.__touchStartCallback__.bind(this));
    this.__window__.addEventListener('touchend', this.__touchEndCallback__.bind(this));
    this.__window__.addEventListener('touchcancel', this.__touchCancelCallback__.bind(this));
    this.__window__.addEventListener('touchmove', this.__touchMoveCallback__.bind(this));
    this.__window__.addEventListener('gamepadconnected', this.__gamepadConnectedCallback__.bind(this));
    this.__window__.addEventListener('gamepaddisconnected', this.__gamepadDisconnectedCallback__.bind(this));
    
    let rect = this.__canvas__.getBoundingClientRect();
    this.__mouse__.offsetX = rect.left;
    this.__mouse__.offsetY = rect.top;
};

Utilities.prototype.hideWindowCursor = function() {
    this.__canvas__.style.cursor = 'none';
};

Utilities.prototype.showWindowCursor = function() {
    this.__canvas__.style.cursor = 'initial';
};

Utilities.prototype.getMouse = function() {
    return this.__mouse__;
};

Utilities.prototype.getMouseX = function() {
    return this.__mouse__.x;
};

Utilities.prototype.getMouseY = function() {
    return this.__mouse__.y;
};

Utilities.prototype.getMouseButtons = function() {
    return this.__mouse__.buttons;
};

Utilities.prototype.isMouseButtonDown = function(code) {
    if (code < 0 || code > 2) {
        return false;
    }
    return this.__mouse__.buttons[code];
};

Utilities.prototype.isKeyDown = function(key) {
    if (!(key in this.__keys__)) {
        return false;
    }
    
    let keyObj = this.__keys__[key];
    return !keyObj.debounced;
};

Utilities.prototype.hasKey = function(key) {
    return key in this.__keys__;
};

Utilities.prototype.debounceKey = function(key) {
    if (!(key in this.__keys__)) {
        return;
    }
    
    this.__keys__[key].debounced = true;
};