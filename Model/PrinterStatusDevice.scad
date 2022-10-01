ledD=5;
h = 5;
fn = 10;
dd = 5;
ledPos = cat([[60, 10], [20, 10], [40, 10], [60, 20], [20, 20], [40, 20], [60, 35], [20, 35]], cat([for (i = [0:4]) [90, i * 7 + 7]], cat([for (i = [0:4]) [97, i * 7 + 7]], [for (i = [0:4]) [122, i * 7 + 7]])));
    echo(ledPos);
difference() {
    union() {
        hull() {
            translate([dd/2, dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
            translate([141 - dd/2, dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
            translate([141 - dd/2, 48 - dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
            translate([dd/2, 48 - dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
        }
        //cube([141, 48, h]);j
        color([0, 1, 0]) translate([3, 6, 0]) cube([65, 8, h + 0.5]);
        color([0, 1, 0]) translate([3, 16, 0]) cube([65, 8, h + 0.5]);
        color([0, 1, 0]) translate([73, 2, 0]) cube([42, 44, h + 0.5]);
        color([0, 1, 0]) translate([117, 2, 0]) cube([22, 44, h + 0.5]);
    }
    
    translate([dd/2, dd/2, 0]) cylinder(d = 1, h = h, $fn = fn); 
    translate([141 - dd/2, dd/2, 0]) cylinder(d = 1, h = 10, $fn = fn); 
    translate([141 - dd/2, 48 - dd/2, 0]) cylinder(d = 1, h = 10, $fn = fn); 
    translate([dd/2, 48 - dd/2, 0]) cylinder(d = 1, h = h, $fn = fn); 

    translate([141 - dd/2, dd/2, h]) cylinder(d = 8, h = 10, $fn = fn); 
    translate([141 - dd/2, 48 - dd/2, h]) cylinder(d = 8, h = 10, $fn = fn); 

    for(i = [0:22]) {
        translate([ledPos[i][0], ledPos[i][1], -0.01]) cylinder(d=ledD, h=h + 1, $fn=fn);
    }
}


translate([4, 8, 0]) textc("BED");
translate([4, 18, 0]) textc("EXT");
translate([11.5, 26, 0]) textc("COOL");
translate([32, 26, 0]) textc("HEAT");
translate([52, 26, 0]) textc("TEMP");
translate([11, 40, 0]) textc("READY");
translate([42, 40, 0]) textc("PRINTING");
for (i = [1:5]) {
translate([75, i * 7 -2 , 0]) textc(str(i*10, "%"));
}
for (i = [1:5]) {
translate([102, i * 7 -2 , 0]) textc(str((i + 5)*10, i == 5?"":"%"));
}
for (i = [1:3]) {
    values = [5, 15, 30];
    translate([127, i * 7 -2 , 0]) textc(str(values[i - 1], "m"));
}
translate([127, 4 * 7 -2 , 0]) textc(str("1h"));
translate([127, 5 * 7 -2 , 0]) textc(str("2h"));

translate([78, 40, 0]) textc("PROGRESS");
translate([120, 40, 0]) textc("ETA");



function cat(L1, L2) = [for(L=[L1, L2], a=L) a];
module textc(texts, size = 4){ 
    color([1, 0, 0]) linear_extrude(h + 1) text(texts, size);
}