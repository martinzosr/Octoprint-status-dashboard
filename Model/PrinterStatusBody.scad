ledD=5;
h = 25;
fn = 10;
dd = 5;

difference() {
    union() {
        hull() {
            translate([dd/2, dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
            translate([141 - dd/2, dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
            translate([141 - dd/2, 48 - dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
            translate([dd/2, 48 - dd/2, 0]) cylinder(d = dd, h = h, $fn = fn); 
        }
    }
    
    translate([dd/2, dd/2, 5]) cylinder(d = 2, h = h, $fn = fn); 
    translate([141 - dd/2, dd/2, 5]) cylinder(d = 2, h = h, $fn = fn); 
    translate([141 - dd/2, 48 - dd/2, 5]) cylinder(d = 2, h = h, $fn = fn); 
    translate([dd/2, 48 - dd/2, 5]) cylinder(d = 2, h = h, $fn = fn); 
    translate([dd, dd, 5]) cube([141 - 2*dd, 48 - 2*dd, h]);
}