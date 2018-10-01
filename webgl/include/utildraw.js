Utilities.prototype.__bgColor__ = '#000';
Utilities.prototype.__fgColor__ = '#fff';
Utilities.prototype.__drawCursor__ = {x: 0, y: 0};

Utilities.prototype.getCanvas = function() {
    return this.__canvas__;
};

Utilities.prototype.getContext = function() {
    return this.__context__;
};

Utilities.prototype.getBackgroundColor = function() {
    return this.__bgColor__;
};

Utilities.prototype.getForegroungColor = function() {
    return this.__fgColor__;
};

Utilities.prototype.getDrawCursor = function() {
    return this.__drawCursor__;
};

Utilities.prototype.setCanvasDimensions = function(width, height) {
    this.__canvas__.width = width;
    this.__canvas__.height = height;
};

Utilities.prototype.fitCanvasToWindow = function() {
    this.__canvas__.width = this.__window__.innerWidth;
    this.__canvas__.height = this.__window__.innerHeight;
};

Utilities.prototype.bindCanvasSizeToWindow = function() {
    this.__window__.addEventListener('resize', fitCanvasToWindow.bind(this));
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

Utilities.prototype.drawPoint = function() {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context__.fillRect(
        this.__drawCursor__.x - 1,
        this.__drawCursor__.y - 1,
        2,
        2
    );
};

Utilities.prototype.strokePolylineXY = function(/* arguments */) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context__.beginPath();
    let x0 = this.__drawCursor__.x + arguments[0];
    let y0 = this.__drawCursor__.y + arguments[1];
    this.__context__.moveTo(x0, y0);
    for (let a = 2; a < arguments.length; a += 2) {
        let x = this.__drawCursor__.x + arguments[a];
        let y = this.__drawCursor__.y + arguments[a + 1];
        this.__context__.lineTo(x, y);
    }
    this.__context__.stroke();
};

Utilities.prototype.strokePolylinePts = function(points) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context__.beginPath();
    let pt0 = points[0];
    let x0 = this.__drawCursor__.x + pt0[0];
    let y0 = this.__drawCursor__.y + pt0[1];
    this.__context__.moveTo(x0, y0);
    for (let p = 1; p < points.length; p++) {
        let pt = points[p];
        let x = this.__drawCursor__.x + pt[0];
        let y = this.__drawCursor__.y + pt[1];
        this.__context__.lineTo(x, y);
    }
    this.__context__.stroke();
};


Utilities.prototype.strokePolygonXY = function(/* arguments */) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context__.beginPath();
    let x0 = this.__drawCursor__.x + arguments[0];
    let y0 = this.__drawCursor__.y + arguments[1];
    this.__context__.moveTo(x0, y0);
    for (let a = 2; a < arguments.length; a += 2) {
        let x = this.__drawCursor__.x + arguments[a];
        let y = this.__drawCursor__.y + arguments[a + 1];
        this.__context__.lineTo(x, y);
    }
    this.__context__.closePath();
    this.__context__.stroke();
};

Utilities.prototype.strokePolygonPts = function(points) {
    this.__context__.strokeStyle = this.__fgColor__;
    this.__context__.beginPath();
    let pt0 = points[0];
    let x0 = this.__drawCursor__.x + pt0[0];
    let y0 = this.__drawCursor__.y + pt0[1];
    this.__context__.moveTo(x0, y0);
    for (let p = 1; p < points.length; p++) {
        let pt = points[p];
        let x = this.__drawCursor__.x + pt[0];
        let y = this.__drawCursor__.y + pt[1];
        this.__context__.lineTo(x, y);
    }
    this.__context__.closePath();
    this.__context__.stroke();
};

Utilities.prototype.fillPolygonXY = function(/* arguments */) {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context__.beginPath();
    let x0 = this.__drawCursor__.x + arguments[0];
    let y0 = this.__drawCursor__.y + arguments[1];
    this.__context__.moveTo(x);
    for (let a = 2; a < arguments.length; a += 2) {
        let x = this.__drawCursor__.x + arguments[a];
        let y = this.__drawCursor__.y + arguments[a + 1];
        this.__context__.lineTo(x, y);
    }
    this.__context__.closePath();
    this.__context__.fill();
};

Utilities.prototype.fillPolygonPts = function(points) {
    this.__context__.fillStyle = this.__fgColor__;
    this.__context__.beginPath();
    let pt0 = points[0];
    let x0 = this.__drawCursor__.x + pt0[0];
    let y0 = this.__drawCursor__.y + pt0[1];
    this.__context__.moveTo(x0, y0);
    for (let p = 1; p < points.length; p++) {
        let pt = points[p];
        let x = this.__drawCursor__.x + pt[0];
        let y = this.__drawCursor__.y + pt[1];
        this.__context__.lineTo(x, y)
    }
    this.__context__.closePath();
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
