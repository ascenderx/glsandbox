Utilities.prototype.__textCursor__ = {x: 0, y: 0};

Utilities.prototype.getTextCursor = function() {
    return this.__textCursor__;
};

Utilities.prototype.setTextCursor = function(x, y) {
    this.__textCursor__.x = x;
    this.__textCursor__.y = y;
};

Utilities.prototype.__strokeGlyph__ = function(character) {
    
};

Utilities.prototype.strokeTextGlyphs = function(text) {
    for (let ch of text) {
        this.__strokeGlyph__(ch);
    }
}

Utilities.prototype.setFont = function(font) {
    this.__context__.font = font;
};

Utilities.prototype.strokeTextFont = function(text) {
    this.__context__.strokeText(
        text,
        this.__textCursor__.x,
        this.__textCursor__.y
    );
};

Utilities.prototype.fillTextFont = function(text) {
    this.__context__.fillText(
        text,
        this.__textCursor__.x,
        this.__textCursor__.y
    );
};