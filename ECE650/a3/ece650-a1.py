import sys
import re
import copy


my_map = dict()


class Street(object):
    def __init__(self, my_map):
        self.my_map = my_map
        
    def add(self, road_name, point):
        self.my_map[road_name] = point

    def mod(self, road_name, point):
        self.my_map[road_name] = point

    def rm(self, road_name):
        del(self.my_map[road_name])


def parseline(line):
    r = re.compile('\s*(add|mod|rm)\s+["]\s*[a-zA-Z\s]*["](\s+[(]\s*[-]?\d+\s*[,]\s*[-]?\d+\s*[)])*')
    if re.match(r,line.replace('\n','')):
        road = re.split(' \"|\" ', line.strip())
        if len(road) >= 2:
            cmd = road[0]
            road_name = road[1].replace('\"','').title()
            global my_map
            s = Street(my_map)
            if len(road) == 3:
                coordinate = road[2].strip().split()
                if len(coordinate) > 1:
                    if cmd.strip() == 'add':
                        if road_name not in s.my_map:
                            point = []
                            for i in range(len(coordinate)):
                                x, y = eval(coordinate[i])
                                x = float(x)
                                y = float(y)
                                point.append((x, y))
                            s.add(road_name, point)
                        else:
                                raise Exception('@a1 input road name already exists')
                    elif cmd.strip() == 'mod':
                            if road_name in s.my_map:
                                point = []
                                for i in range(len(coordinate)):
                                    x, y = eval(coordinate[i])
                                    x = float(x)
                                    y = float(y)
                                    point.append((x, y))
                                s.mod(road_name, point)
                            else:
                                raise Exception('@a1 input road name does not exists')
                    else:
                        raise Exception('@a1 wrong input')
                else:
                    raise Exception('@a1 need at least 2 coordinates')
            elif len(road) == 2: 
                if cmd.strip() == 'rm':
                    if road_name in s.my_map:
                        s.rm(road_name)
                    else:
                        raise Exception('@a1 input road name does not exists')
                else:
                    raise Exception('@a1 wrong input')
            my_map=s.my_map            
    else:
        raise Exception('@a1 a valid input is like: add|mod + "street name" + coordinates or rm + "street name"')
                
    
class Printer(object):
    def __init__(self):
        return None

    def gg(self, verties, edges):
        E = 'E {'
        for i in range(len(edges)):
            coor1 = verties.index(edges[i][0]) + 1
            coor2 = verties.index(edges[i][1]) + 1
            if i < (len(edges)-1):
                e = '<{0},{1}>,'.format(coor1,coor2)
            if i == (len(edges)-1):
                e = '<{0},{1}>'.format(coor1,coor2)
            E = E + e
        E = E +'}' 
        V = 'V {0}'.format(len(verties))
        if (V == "V 0" and E == "E "+"{"+"}"):
            return None
        else:
            print(V)
            print(E)
            sys.stdout.flush()


class Point(object):
    def __init__(self, coor):
        self.x = float(coor[0])
        self.y = float(coor[1])
        
    def __repr__(self):
        return (self.x, self.y)


class Line(object):
    def __init__(self, p1, p2):
        self.src = p1
        self.dst = p2 
        
        
def cross(p1,p2,p3):
    x1=p2[0]-p1[0]
    y1=p2[1]-p1[1]
    x2=p3[0]-p1[0]
    y2=p3[1]-p1[1]
    return x1*y2-x2*y1   
            
      
def intersect(l1, l2):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y
    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
    if (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) != 0:
        xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
    else: return False
    xcoor =  xnum / xden
    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
    if (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) != 0:
        yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    else: return False
    ycoor = ynum / yden
    #use line segment striddle to test whether coordinates out of boundary
    if cross((x1,y1), (x2,y2), (x3,y3)) * cross((x1,y1), (x2,y2), (x4,y4)) <= 0\
        and cross((x3,y3), (x4,y4), (x1,y1)) * cross((x3,y3), (x4,y4), (x2,y2)) <= 0:
        return (xcoor, ycoor)
    else: return False        


class Generator(object):
    def __init__(self):
        return None
        
    def get_ve(self):
        edges = []
        verties = []
        line_map = dict()
        verties_map = dict()
        intersect_map = dict()
        # get line_map dict
        for keys, values in my_map.items():
            line = []
            for i in range(len(values)):
                if i+1 < len(values):
                    p1 = Point(values[i])
                    p2 = Point(values[(i+1)])
                    l = Line(p1, p2)
                    line.append(l)
            line_map[keys] = line
        #get intersect_map dict
        keys = list(line_map.keys())
        for k in range(len(keys)):
            if k+1 < len(keys):
                 for l in range(k+1,len(keys)):
                    #street1's line segment list
                    subset1 = line_map[keys[k]]
                    #street2's line segment list
                    subset2 = line_map[keys[(l)]]
                    for i in range(len(subset1)):
                        for j in range(len(subset2)):
                            if bool(intersect(subset1[i],subset2[j])):
                                (x, y) = intersect(subset1[i],subset2[j]) #it is a line segments in street 1 line segment list and street 2 line segment list
                                intersect_map['{0}'.format([keys[k], keys[l], (subset1[i].src.x,subset1[i].src.y), (subset1[i].dst.x,subset1[i].dst.y),\
                                (subset2[j].src.x,subset2[j].src.y), (subset2[j].dst.x,subset2[j].dst.y)])] = (x,y)
        #get verties
        verties_map = copy.deepcopy(my_map)
        li1 = []
        for i in intersect_map.keys():
            key_infor = eval(i)
            li1.append(key_infor[0])
            li1.append(key_infor[1])
        li1 = list(set(li1))
        li2 = []
        for key in verties_map.keys():
            if key not in li1:
                li2.append(key)
        for item in li2:
            #here is the reason of problem!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            del(verties_map[item])           
        for k1, v1 in my_map.items():
            flag = 0
            if len(v1) == 2:
                flag =1
            for k2, v2 in intersect_map.items():
                key_infor = eval(k2)
                if k1 == key_infor[0]:
                    for i in v1:
                        if i == key_infor[2]:
                            if verties_map[k1][verties_map[k1].index(i)+1] == key_infor[3]:
                                if v2 != key_infor[2] and key_infor[3]:
                                    verties_map[k1].insert(verties_map[k1].index(i)+1,v2)
                            else:
                                len1 = (verties_map[k1][verties_map[k1].index(i)+1][0]-i[0])**2\
                                + (verties_map[k1][verties_map[k1].index(i)+1][1]-i[1])**2
                                len2 = (v2[0]-i[0])**2 + (v2[1]-i[1])**2
                                if len1 < len2:
                                   if v2 != key_infor[2] and key_infor[3]:
                                       verties_map[k1].insert(verties_map[k1].index(i)+2,v2)
                                if len1 > len2:
                                   if v2 != key_infor[2] and key_infor[3]:
                                       verties_map[k1].insert(verties_map[k1].index(i)+1,v2)
                elif k1 == key_infor[1]:
                    for i in v1:
                        if i == key_infor[4]:
                            if verties_map[k1][verties_map[k1].index(i)+1] == key_infor[5]:
                                if v2 != key_infor[4] and key_infor[5]:
                                    verties_map[k1].insert(verties_map[k1].index(i)+1,v2)
                            else:
                                len1 = (verties_map[k1][verties_map[k1].index(i)+1][0]-i[0])**2\
                                + (verties_map[k1][verties_map[k1].index(i)+1][1]-i[1])**2
                                len2 = (v2[0]-i[0])**2 + (v2[1]-i[1])**2
                                if len1 < len2:
                                   if v2 != key_infor[2] and key_infor[3]:
                                       verties_map[k1].insert(verties_map[k1].index(i)+2,v2)
                                if len1 > len2:
                                   if v2 != key_infor[2] and key_infor[3]:
                                       verties_map[k1].insert(verties_map[k1].index(i)+1,v2)
                
            temp = []
            if k1 in list(verties_map.keys()):
                if flag == 0:
                    del(verties_map[k1][0])
                for i in verties_map[k1]:
                    if not i in temp:
                        temp.append(i)
                verties_map[k1] = temp
            
        for value in verties_map.values():
            verties.extend(value)
        verties = list(set(verties))                      
        #get edges
        for k1, v1 in verties_map.items():
            list1 = []
            for k2, v2 in intersect_map.items():
                key_infor = eval(k2)
                if k1 == key_infor[0] or key_infor[1]:
                    key_infor.append(v2)
                    list1.extend(key_infor)
            list1 = list(set(list1))
            list2 =[i for i in v1 if i in list1]
            for i in range(len(list2)):
                if i+1 < len(list2):
                    j = [[list2[i],list2[i+1]]]
                    edges.extend(j)
        intersects = list(intersect_map.values())
        intersects = list(set(intersects))
        list1 = []
        for i in edges:
            if i[0] not in intersects and i[1] not in intersects:
                list1.append(i)
        for item in list1:
            edges.remove(item)
        return  verties, edges                  

                                             
def main():
    while True:
        try:
            line = sys.stdin.readline()
            if line.replace('\n','') == '':
                break
            elif line.replace('\n','') == 'gg':
                g = Generator()
                verties, edges = g.get_ve()
                p = Printer()
                p.gg(verties, edges)
            else:
                parseline(line)
                for key in my_map.keys():
                    if len(my_map[key]) != len(set(my_map[key])):
                        raise Exception('form child_a1, repeatd point @ '+key+', please mod this street again')
        except Exception as e:
            print('Error: from child_a1 ' + str(e), file=sys.stderr)
    # print('')
    sys.exit(0)            
    

if __name__ == "__main__":
    main()
