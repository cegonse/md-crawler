// Create animation curves in C
// (c) Cesar Gonzalez Segura 2017
var fs = require("fs");

// Easing functions
// Based on https://gist.github.com/gre/1650294

// No easing, no acceleration
function linear( t ) {
    return t;
}

// Slight acceleration from zero to full speed
function easeInSine( t ) {
    return -1 * Math.cos( t * ( Math.PI / 2 ) ) + 1;
}

// Slight deceleration at the end
function easeOutSine( t ) {
    return Math.sin( t * ( Math.PI / 2 ) );
}

// Slight acceleration at beginning and slight deceleration at end
function easeInOutSine( t ) {
    return -0.5 * ( Math.cos( Math.PI * t ) - 1 );
}

// Accelerating from zero velocity
function easeInQuad( t ) {
    return t * t;
}

// Decelerating to zero velocity
function easeOutQuad( t ) {
    return t * ( 2 - t );
}

// Acceleration until halfway, then deceleration
function easeInOutQuad( t ) {
    return t < 0.5 ? 2 * t * t : - 1 + ( 4 - 2 * t ) * t;
}

// Accelerating from zero velocity
function easeInCubic( t ) {
    return t * t * t;
}

// Decelerating to zero velocity
function easeOutCubic( t ) {
    const t1 = t - 1;
    return t1 * t1 * t1 + 1;
}

// Acceleration until halfway, then deceleration
function easeInOutCubic( t ) {
    return t < 0.5 ? 4 * t * t * t : ( t - 1 ) * ( 2 * t - 2 ) * ( 2 * t - 2 ) + 1;
}

// Accelerating from zero velocity
function easeInQuart( t ) {
    return t * t * t * t;
}

// Decelerating to zero velocity
function easeOutQuart( t ) {
    const t1 = t - 1;
    return 1 - t1 * t1 * t1 * t1;
}

// Acceleration until halfway, then deceleration
function easeInOutQuart( t ) {
    const t1 = t - 1;
    return t < 0.5 ? 8 * t * t * t * t : 1 - 8 * t1 * t1 * t1 * t1;
}

// Accelerating from zero velocity
function easeInQuint( t ) {
    return t * t * t * t * t;
}

// Decelerating to zero velocity
function easeOutQuint( t ) {
    const t1 = t - 1;
    return 1 + t1 * t1 * t1 * t1 * t1;
}

// Acceleration until halfway, then deceleration
function easeInOutQuint( t ) {
    const t1 = t - 1;
    return t < 0.5 ? 16 * t * t * t * t * t : 1 + 16 * t1 * t1 * t1 * t1 * t1;
}

// Accelerate exponentially until finish
function easeInExpo( t ) {

    if( t === 0 ) {
        return 0;
    }

    return Math.pow( 2, 10 * ( t - 1 ) );

}

// Initial exponential acceleration slowing to stop
function easeOutExpo( t ) {

    if( t === 1 ) {
        return 1;
    }

    return ( -Math.pow( 2, -10 * t ) + 1 );

}

// Exponential acceleration and deceleration
function easeInOutExpo( t ) {
    
    if( t === 0 || t === 1 ) {
        return t;
    }

    const scaledTime = t * 2;
    const scaledTime1 = scaledTime - 1;

    if( scaledTime < 1 ) {
        return 0.5 * Math.pow( 2, 10 * ( scaledTime1 ) );
    }

    return 0.5 * ( -Math.pow( 2, -10 * scaledTime1 ) + 2 );

}

// Increasing velocity until stop
function easeInCirc( t ) {

    const scaledTime = t / 1;
    return -1 * ( Math.sqrt( 1 - scaledTime * t ) - 1 );

}

// Start fast, decreasing velocity until stop
function easeOutCirc( t ) {

    const t1 = t - 1;
    return Math.sqrt( 1 - t1 * t1 );

}

// Fast increase in velocity, fast decrease in velocity
function easeInOutCirc( t ) {

    const scaledTime = t * 2;
    const scaledTime1 = scaledTime - 2;

    if( scaledTime < 1 ) {
        return -0.5 * ( Math.sqrt( 1 - scaledTime * scaledTime ) - 1 );
    }

    return 0.5 * ( Math.sqrt( 1 - scaledTime1 * scaledTime1 ) + 1 );

}

// Slow movement backwards then fast snap to finish
function easeInBack( t, magnitude = 1.70158 ) {

    return t * t * ( ( magnitude + 1 ) * t - magnitude );

}

// Fast snap to backwards point then slow resolve to finish
function easeOutBack( t, magnitude = 1.70158 ) {

    const scaledTime = ( t / 1 ) - 1;
    
    return (
        scaledTime * scaledTime * ( ( magnitude + 1 ) * scaledTime + magnitude )
    ) + 1;

}

// Slow movement backwards, fast snap to past finish, slow resolve to finish
function easeInOutBack( t, magnitude = 1.70158 ) {

    const scaledTime = t * 2;
    const scaledTime2 = scaledTime - 2;

    const s = magnitude * 1.525;

    if( scaledTime < 1) {

        return 0.5 * scaledTime * scaledTime * (
            ( ( s + 1 ) * scaledTime ) - s
        );

    }

    return 0.5 * (
        scaledTime2 * scaledTime2 * ( ( s + 1 ) * scaledTime2 + s ) + 2
    );

}
// Bounces slowly then quickly to finish
function easeInElastic( t, magnitude = 0.7 ) {

    if( t === 0 || t === 1 ) {
        return t;
    }

    const scaledTime = t / 1;
    const scaledTime1 = scaledTime - 1;

    const p = 1 - magnitude;
    const s = p / ( 2 * Math.PI ) * Math.asin( 1 );

    return -(
        Math.pow( 2, 10 * scaledTime1 ) *
        Math.sin( ( scaledTime1 - s ) * ( 2 * Math.PI ) / p )
    );

}

// Fast acceleration, bounces to zero
function easeOutElastic( t, magnitude = 0.7 ) {

    const p = 1 - magnitude;
    const scaledTime = t * 2;

    if( t === 0 || t === 1 ) {
        return t;
    }

    const s = p / ( 2 * Math.PI ) * Math.asin( 1 );
    return (
        Math.pow( 2, -10 * scaledTime ) *
        Math.sin( ( scaledTime - s ) * ( 2 * Math.PI ) / p )
    ) + 1;

}

// Slow start and end, two bounces sandwich a fast motion
function easeInOutElastic( t, magnitude = 0.65 ) {

    const p = 1 - magnitude;

    if( t === 0 || t === 1 ) {
        return t;
    }

    const scaledTime = t * 2;
    const scaledTime1 = scaledTime - 1;
    
    const s = p / ( 2 * Math.PI ) * Math.asin( 1 );

    if( scaledTime < 1 ) {
        return -0.5 * (
            Math.pow( 2, 10 * scaledTime1 ) *
            Math.sin( ( scaledTime1 - s ) * ( 2 * Math.PI ) / p )
        );
    }

    return (
        Math.pow( 2, -10 * scaledTime1 ) *
        Math.sin( ( scaledTime1 - s ) * ( 2 * Math.PI ) / p ) * 0.5
    ) + 1;

}

// Bounce to completion
function easeOutBounce( t ) {

    const scaledTime = t / 1;

    if( scaledTime < ( 1 / 2.75 ) ) {

        return 7.5625 * scaledTime * scaledTime;

    } else if( scaledTime < ( 2 / 2.75 ) ) {

        const scaledTime2 = scaledTime - ( 1.5 / 2.75 );
        return ( 7.5625 * scaledTime2 * scaledTime2 ) + 0.75;

    } else if( scaledTime < ( 2.5 / 2.75 ) ) {

        const scaledTime2 = scaledTime - ( 2.25 / 2.75 );
        return ( 7.5625 * scaledTime2 * scaledTime2 ) + 0.9375;

    } else {

        const scaledTime2 = scaledTime - ( 2.625 / 2.75 );
        return ( 7.5625 * scaledTime2 * scaledTime2 ) + 0.984375;

    }

}

// Bounce increasing in velocity until completion
function easeInBounce( t ) {
    return 1 - easeOutBounce( 1 - t );
}

// Bounce in and bounce out
function easeInOutBounce( t ) {

    if( t < 0.5 ) {

        return easeInBounce( t * 2 ) * 0.5;
        
    }

    return ( easeOutBounce( ( t * 2 ) - 1 ) * 0.5 ) + 0.5;

}

var easingFuncs = [
    ["linear", linear],
    ["easeInSine", easeInSine],
    ["easeOutSine", easeOutSine],
    ["easeInOutSine", easeInOutSine],
    ["easeInQuad", easeInQuad],
    ["easeOutQuad", easeOutQuad],
    ["easeInOutQuad", easeInOutQuad],
    ["easeInCubic", easeInCubic],
    ["easeOutCubic", easeOutCubic],
    ["easeInOutCubic", easeInOutCubic],
    ["easeInQuart", easeInQuart],
    ["easeOutQuart", easeOutQuart],
    ["easeInOutQuart", easeInOutQuart],
    ["easeInQuint", easeInQuint],
    ["easeOutQuint", easeOutQuint],
    ["easeInOutQuint", easeInOutQuint],
    ["easeInExpo", easeInExpo],
    ["easeOutExpo", easeOutExpo],
    ["easeInOutExpo", easeInOutExpo],
    ["easeInCirc", easeInCirc],
    ["easeOutCirc", easeOutCirc],
    ["easeInOutCirc", easeInOutCirc],
    ["easeInBack", easeInBack],
    ["easeOutBack", easeOutBack],
    ["easeInOutBack", easeInOutBack],
    ["easeInElastic", easeInElastic],
    ["easeOutElastic", easeInElastic],
    ["easeInOutElastic", easeInElastic],
    ["easeInBounce", easeInBounce],
    ["easeOutBounce", easeOutBounce],
    ["easeInOutBounce", easeInOutBounce]
];

if (process.argv.length != 8) {
    console.log("Usage: curve2c [curve_type] [start] [end] [steps] [name] [data_type]");
    console.log("- Available easing functions:");

    for (var i = 0; i < easingFuncs.length; ++i) {
        console.log("- " + easingFuncs[i][0]);
    }

	process.exit(1);
}

var curveType = process.argv[2];
var start = process.argv[3];
var end = process.argv[4];
var steps = process.argv[5];
var curveName = process.argv[6];
var dataType = process.argv[7];

// Find the easing function
var easingPtr = null;

for (var i = 0; i < easingFuncs.length; ++i) {
    if (easingFuncs[i][0] === curveType) {
        easingPtr = easingFuncs[i][1];
    }
}

// Generate the base curve
var p = Array(steps);

for (var i = 0; i < steps; ++i) {
    p[i] = i / steps;
    p[i] = easingPtr(p[i]);
}

// Scale to the target start and end
for (var i = 0; i < steps; ++i) {
    p[i] *= end;
    p[i] += start;
    
    if (dataType == "fix16") {
        p[i] = "FIX16(" + p[i] + ")";
    } else if (dataType == "fix32") {
        p[i] = "FIX32(" + p[i] + ")";
    } else {
        p[i] = Math.floor(p[i]);
    }
}

// Print out the C code
process.stdout.write("#define " + curveName + "_LENGTH\t" + steps.toString() + "\n\n");
process.stdout.write("static const " + dataType + " " + curveName + "[" + steps + "] = {\n\t");

for (var i = 0; i < p.length; ++i) {
    process.stdout.write(p[i].toString());

    if (i != p.length - 1) {
        process.stdout.write(", ");
    } else {
        process.stdout.write("\n")
    }
    
    if (i % 10 == 0 && i != 0) {
        process.stdout.write("\n\t");
    }
}

console.log("};");