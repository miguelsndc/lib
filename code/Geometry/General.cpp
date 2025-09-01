
ld dist  (Point a, Point b){ return sqrtl((a-b)*(a-b)); }	                   // distance from A to B
ld angle (Point a, Point b){ return acos((a*b) / sqrtl(a*a) / sqrtl(b*b)); } //Angle between A and B
Point rotate(Point p, double ang){ return Point(p.x*cos(ang) - p.y*sin(ang), p.x*sin(ang) + p.y*cos(ang)); } //Left rotation. Angle in radian

ll Area(vector<Point>& p){
  ll area = 0;  
  for(int i=2; i < p.size(); i++)
    area += (p[i]-p[0]) % (p[i-1]-p[0]);
  return abs(area) / 2LL;
}

// Intersecao entre duas retas definidas por a1 + td1 e a2 + td2
// se retas forem paralelas d1 % d2 = 0
Point intersect(Point a1, Point d1, Point a2, Point d2){
  return a1 + d1 * (((a2 - a1)%d2) / (d1%d2));
}

ld dist_pt_line(Point a, Point l1, Point l2){ 
	return abs( ((a-l1) % (l2-l1)) / dist(l1, l2)  ); 
}

ld dist_pt_segm(Point a, Point s1, Point s2){
  if(s1 == s2) return dist(s1, a);
  
  Point d = s2 - s1;
  ld t = max(0.0L, min(1.0L, ((a-s1)*d) / sqrtl(d*d)) );

  return dist(a, s1+(d*t));
}