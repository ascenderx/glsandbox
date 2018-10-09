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
    this.__canvas__.style.position = "absolute";
    this.__canvas__.style.left = 0;
    this.__canvas__.style.top = 0;
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

Utilities.prototype.__makeRect__ = function(width, height, drawMethod) {
    let style;
    let func;
    
    switch (drawMethod) {
        case 'stroke':
            style = 'strokeStyle';
            func = 'strokeRect';
            break;
            
        case 'fill':
            style = 'fillStyle';
            func = 'fillRect';
            break;
        
        default:
            throw 'Invalid draw method';
    }
    
    this.__context__[style] = this.__fgColor__;
    this.__context__[func](
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        width,
        height
    );
};

Utilities.prototype.strokeRect = function(width, height) {
    this.__makeRect__(width, height, 'stroke');
};

Utilities.prototype.fillRect = function(width, height) {
    this.__makeRect__(width, height, 'fill');
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

Utilities.prototype.__makePolyXY__ = function(drawMethod, closePath, args) {
    let style;
    
    switch (drawMethod) {
        case 'stroke':
            style = 'strokeStyle';
            break;
            
        case 'fill':
            style = 'fillStyle';
            break;
        
        default:
            throw 'Invalid draw method';
    }
    
    this.__context__[style] = this.__fgColor__;
    this.__context__.beginPath();
    let x0 = this.__drawCursor__.x + args[0];
    let y0 = this.__drawCursor__.y + args[1];
    this.__context__.moveTo(x0, y0);
    for (let a = 2; a < args.length; a += 2) {
        let x = this.__drawCursor__.x + args[a];
        let y = this.__drawCursor__.y + args[a + 1];
        this.__context__.lineTo(x, y);
    }
    if (closePath) {
        this.__context__.closePath();
    }
    this.__context__[drawMethod]();
};

Utilities.prototype.__makePolyPts__ = function(drawMethod, closePath, pts) {
    let style;
    
    switch (drawMethod) {
        case 'stroke':
            style = 'strokeStyle';
            break;
            
        case 'fill':
            style = 'fillStyle';
            break;
        
        default:
            throw 'Invalid draw method';
    }
    
    this.__context__[style] = this.__fgColor__;
    this.__context__.beginPath();
    let pt0 = pts[0];
    let x0 = this.__drawCursor__.x + pt0[0];
    let y0 = this.__drawCursor__.y + pt0[1];
    this.__context__.moveTo(x0, y0);
    for (let pt of pts) {
        let x = this.__drawCursor__.x + pt[0];
        let y = this.__drawCursor__.y + pt[1];
        this.__context__.lineTo(x, y);
    }
    if (closePath) {
        this.__context__.closePath();
    }
    this.__context__[drawMethod]();
};

Utilities.prototype.strokePolylineXY = function(/* arguments */) {
    this.__makePolyXY__('stroke', false, arguments);
};

Utilities.prototype.strokePolylinePts = function(points) {
    this.__makePolyPts__('stroke', false, points);
};

Utilities.prototype.strokePolygonXY = function(/* arguments */) {
    this.__makePolyXY__('stroke', true, arguments);
};

Utilities.prototype.strokePolygonPts = function(points) {
    this.__makePolyPts__('stroke', true, points);
};

Utilities.prototype.fillPolygonXY = function(/* arguments */) {
    this.__makePolyXY__('fill', true, arguments);
};

Utilities.prototype.fillPolygonPts = function(points) {
    this.__makePolyPts__('fill', true, points);
};

Utilities.prototype.__makeArc__ = function(radius, angle0, angle1, drawMethod) {
    let style;
    
    switch (drawMethod) {
        case 'stroke':
            style = 'strokeStyle';
            break;
            
        case 'fill':
            style = 'fillStyle';
            break;
        
        default:
            throw 'Invalid draw method';
    }
    
    this.__context__[style] = this.__fgColor__;
    this.__context__.arc(
        this.__drawCursor__.x,
        this.__drawCursor__.y,
        radius,
        angle0,
        angle1
    );
    this.__context__[drawMethod]();
};

Utilities.prototype.strokeCircle = function(radius) {
    this.__makeCircle__(radius, 0, 2 * Math.PI, 'stroke');
};

Utilities.prototype.fillCircle = function(radius) {
    this.__makeCircle__(radius, 0, 2 * Math.PI, 'fill');
};

Utilities.prototype.strokeArc = function(radius, angle0, angle1) {
    this.__makeCircle__(radius, angle0, angle1, 'stroke');
};

Utilities.prototype.fillArc = function(radius, angle0, angle1) {
    this.__makeCircle__(radius, angle0, angle1, 'fill');
};