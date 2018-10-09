Utilities.randFloat = function(minimum, maximum) {
    return Math.random() * (maximum - minimum + 1) + minimum;
};

Utilities.randInt = function(minimum, maximum) {
    return Math.floor(randFloat(minimum, maximum));
}

Utilities.degToRad = function(degrees) {
    return (degrees * Math.PI) / 180.0;
};

Utilities.radToDeg = function(radians) {
    return (radians * 180.0) / Math.PI;
};

Utilities.rotateXYAboutCenter = function(x0, y0, xc, yc, angle) {
    let radians = this.degToRad(angle);
    let cosA = Math.cos(radians);
    let sinA = Math.sin(radians);
    let x1 = x0 * cosA - y0 * sinA;
    let y1 = x0 * sinA + y0 * cosA;
    
    let ptNew = [x1 + xc, y1 + yc];
    return ptNew;
}; 

Utilities.rotatePtAboutCenter = function(pt, center, angle) {
    return this.rotateXYAboutCenter(pt[0], pt[1], center[0], center[1], angle);
};

Utilities.rotatePtsAboutCenter = function(pts, center, angle) {
    let ptsNew = [];
    
    for (let pt of pts) {
        ptsNew.push(this.rotateXYAboutCenter(pt[0], pt[1], center[0], center[1], angle));
    }
    
    return ptsNew;
};

Utilities.rotateXY = function(x0, y0, angle) {
    return this.rotateXYAboutCenter(x0, y0, 0, 0, angle);
};

Utilities.rotatePt = function(pt, angle) {
    return this.rotateXYAboutCenter(pt[0], pt[1], 0, 0, angle);
};

Utilities.rotatePts = function(pts, angle) {
    return this.rotatePtsAboutCenter(pts, [0, 0], angle);
};