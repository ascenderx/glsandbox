Utilities.prototype.__bgColor__ = '#000';
Utilities.prototype.__fgColor__ = '#fff';
Utilities.prototype.__drawCursor__ = {x: 0, y: 0};

Utilities.prototype.getCanvas = function() {
    return this.__canvas__;
};

Utilities.prototype.getContext = function() {
    return this.__context__;
};

Utilities.prototype.getBGColor = function() {
    return this.__bgColor__;
};

Utilities.prototype.getFGColor = function() {
    return this.__fgColor__;
};

Utilities.prototype.getDrawCursor = function() {
    return this.__drawCursor__;
};

Utilities.prototype.setCanvasDimensions = function(width, height) {
    this.__canvas__.width = width;
    this.__canvas__.height = height;
};

Utilities.prototype.setBackgroundColor = function(color) {
    this.__bgColor__ = color;
};

Utilities.prototype.setForegroundColor = function(color) {
    this.__fgColor__ = color;
};

Utilities.prototype.setDrawCursor = function(x, y) {
    this.__drawCursor__.x = x;
    this.__drawCursor__.y = y;
};

Utilities.prototype.drawBackground = function() {
    this.__context__.fillStyle = this.__bgColor__;
    this.__context__.fillRect(0, 0, this.__canvas__.width, this.__canvas__.height);
};

Utilities.prototype.clearCanvas = function() {
    this.__context__.clearRect(0, 0, this.__canvas__.width, this.__canvas__.height);
};

Utilities.prototype.strokeRect = function(width, height) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context__.strokeRect(
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        width,
        height
    );
};

Utilities.prototype.fillRect = function(width, height) {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context__.fillRect(
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        width,
        height
    );
};

Utilities.prototype.strokePolyXY = function(/* arguments */) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context.__beginPath();
    this.__context.moveTo(this.__drawCursor__.x, this.__drawCursor__.y);
    for (let a = 0; a < arguments.length; a += 2) {
        let x = arguments[a];
        let y = arguments[a + 1] || x;
        this.__context__.lineTo(x, y);
    }
    this.__context__.stroke();
};

Utilities.prototype.strokePolyPts = function(points) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context.__beginPath();
    this.__context.moveTo(this.__drawCursor__.x, this.__drawCursor__.y);
    for (let p = 0; p < points.length; p++) {
        let pt = points[p];
        this.__context__.lineTo(pt.x, pt.y);
    }
    this.__context__.stroke();
};

Utilities.prototype.fillPolyXY = function(/* arguments */) {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context.__beginPath();
    this.__context.moveTo(this.__drawCursor__.x, this.__drawCursor__.y);
    for (let a = 0; a < arguments.length; a += 2) {
        let x = arguments[a];
        let y = arguments[a + 1] || x;
        this.__context__.lineTo(x, y);
    }
    this.__context__.fill();
};

Utilities.prototype.fillPolyPts = function(points) {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context.__beginPath();
    this.__context.moveTo(this.__drawCursor__.x, this.__drawCursor__.y);
    for (let p = 0; p < points.length; p++) {
        let pt = points[p];
        this.__context__.lineTo(pt.x, pt.y);
    }
    this.__context__.fill();
};

Utilities.prototype.strokeCircle = function(radius) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context__.arc(
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        radius,
        0,
        Math.PI
    );
    this.__context__.stroke();
};

Utilities.prototype.fillCircle = function(radius) {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context__.arc(
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        radius,
        0,
        Math.PI
    );
    this.__context__.fill();
};

Utilities.prototype.strokeArc = function(radius, angle0, angle1) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context__.arc(
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        radius,
        angle0,
        angle1
    );
    this.__context__.stroke();
};

Utilities.prototype.fillArc = function(radius, angle0, angle1) {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context__.arc(
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        radius,
        angle0,
        angle1
    );
    this.__context__.fill();
};
