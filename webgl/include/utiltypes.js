function Utilities(win, canvas) {
    if (!win) {
        throw "Undefined window";
    } else if (!canvas) {
        throw "Undefined canvas";
    }
    
    this.__window__ = win;
    this.__canvas__ = canvas;
    this.__context__ = canvas.getContext('2d');
}