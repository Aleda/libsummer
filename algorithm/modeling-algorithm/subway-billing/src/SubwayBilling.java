/**
 * @brief: SubwayBilling
 * @version: v1.0
 * @author: wujie(404732744@qq.com)
 * @date: 2014/11/2 01:07
 * @env: Linux version 2.6.32_1-8-0-0
 *       java version "1.6.0_32"
 *       Java(TM) SE Runtime Environment (build 1.6.0_32-b05)
 *       Java HotSpot(TM) 64-Bit Server VM (build 20.7-b02, mixed mode)
 */

import java.util.*;
import java.io.*;

class Edge {
	private String from; /**起始站*/
	private String to; /**临接站*/
	private int dis; /**距离*/
	private int next;
	public Edge() {
		dis = 1;
		next = -1;
	}
	
	/**
	 * @brief: 构建边的方法
	 * @param[in]: from  String  起始站
	 * @param[in]: to    String  临街站
	 * @param[in]: dis   int     距离(默认为1) 
	 * @return :
	 */
	public void setEdge(String from, String to, Vector<String> trans, HashMap<String, Vector<Edge>> headList) {
		this.from = from;
		this.to = to;
		this.dis = 1;
		/**
		if (!trans.contains(from) && !trans.contains(to)) {
			this.dis = 1;
		}
		else if (trans.contains(from) && trans.contains(to)) {
			this.dis = 8;
		}
		else {
			this.dis = 4;
		}
		**/
		headList.get(from).add(this);
	}
	
	/**
	 * @brief: setter and getter
	 */
	public void setFrom(String from) {
		this.from = from;
	}
	public String getFrom() {
		return this.from;
	}
	public void setTo(String to) {
		this.to = to;
	}
	public String getTo() {
		return this.to;
	}
	public void setDis(int dis) {
		this.dis = dis;
	}
	public int getDis() {
		return this.dis;
	}
}

public class SubwayBilling {
	
	private static final String MAP_FILE = "./script/subway.map";
	private static final String STATION_FILE = "./script/stations.list";
	private static final String IN_FILE = "./in.txt";
	private static final int DEFAULT_BUF_SIZE = 1024;
	private static final int DEFAULT_EDGE_NUM = 1000;
	private static final int DEFAULT_STATION_NUM = 80;
	private static final int MAX_DISTANCE_LENGTH = Integer.MAX_VALUE - 9999; /**最大distance*/
	
	//private static Vector<Edge> edges = new Vector<Edge>(DEFAULT_EDGE_NUM); /**所有的边*/
	private static Vector<String> stations = new Vector<String>(DEFAULT_STATION_NUM); /**所有的站*/
	
	private static HashMap<String, Integer> distances = new HashMap<String, Integer>(); /**用来存储距离*/
	private static HashMap<String, Boolean> inq = new HashMap<String, Boolean>(); /**用来标记是否在队列中*/
	private static HashMap<String, Vector<Edge>> head = new HashMap<String, Vector<Edge>>(); /**头结点*/
	private static Vector<String> transfer = new Vector<String>(10); /**储存所有的transfer站*/
	private static HashMap<String, Integer> use = new HashMap<String, Integer>(); /**判断是否存在负环*/
	private static HashMap<String, String> route = new HashMap<String, String>(); /**记录路径*/
	
	/**
	 * @brief: init the distance and inq
	 * 
	 */
	public static void initDistance() {
		for (int i = 0; i < stations.size(); i++) {
			distances.put(stations.get(i), MAX_DISTANCE_LENGTH);
			inq.put(stations.get(i), false);
			use.put(stations.get(i), 0);
		}
	}
	/**
	 * @brief:  SPFA
	 * @param[in]: start String  起点
	 * @param[in]: end   String  终点
	 * @return:    !=-1  int     successful
	 *             -1    int     fail 
	 */
	public static int SPFA(String start, String end) {
		initDistance();
		Queue<String> stationQueue = new LinkedList<String>();
		stationQueue.clear();
		stationQueue.offer(start);
		// 初始起点 dis = 0；
		if (transfer.contains(start)) {
			distances.put(start, 4);
		} else {
			distances.put(start, 0);
		}
		while (stationQueue.size() != 0) {
			String visiting = stationQueue.poll();
			inq.put(visiting, false);
			Vector<Edge> edgs = head.get(visiting);
			for (Edge e: edgs) {
				String from = e.getFrom();
				String to = e.getTo();
				int dis = e.getDis();
				if (transfer.contains(to)) {
					dis = 4;
				}
				if (distances.get(visiting) + dis < distances.get(to)) {
					distances.remove(to);
					//System.out.println("visiting = " + visiting);
					//System.out.println("to = " + to);
					//System.out.println("dis_update = " + (distances.get(visiting) + dis));
					distances.put(to, distances.get(visiting) + dis);
					route.put(to, visiting);
					if (!inq.get(to)) {
						stationQueue.offer(to);
						if (use.get(to) >= DEFAULT_STATION_NUM) { //判断是否出现负环
							return -1;
						}
						inq.put(to, true);
					}
				}
			}
			
		}
		return distances.get(end);
	}
	
	/**
	 * @brief: 读取所有的站
	 * @return: true  boolean 读取成功
	 *          false boolean 读取失败
	 */
	public static boolean getStation() {
		File station = new File(STATION_FILE);
		FileInputStream fis = null;
		InputStreamReader isr = null;
		BufferedReader br = null;
		try {
			fis = new FileInputStream(station);
			isr = new InputStreamReader(fis, "UTF-8");
			br = new BufferedReader(isr);
			String line = "";
			String[] sites = null;
			while ((line = br.readLine()) != null) {
				stations.addElement(line);
				Vector<Edge> v = new Vector<Edge>();
				head.put(line, v);
			}
		} catch (IOException e) {
			System.out.println("station文件读入异常");
			return false;
		} finally {
			try {
				br.close();
				isr.close();
				fis.close();
			} catch (IOException e) {
				System.out.println("station文件关闭异常");
				return false;
			}
		}
		return true;

	}
	
	/**
	 * @brief: 构建地铁map
	 * @return: true  boolean 构建成功
	 *          false boolean 构建失败
	 */
	public static boolean buildEdges() {
		File map = new File(MAP_FILE);
		FileInputStream fis = null;
		InputStreamReader isr = null;
		BufferedReader br = null;
		try {
			fis = new FileInputStream(map);
			isr = new InputStreamReader(fis, "UTF-8");
			br = new BufferedReader(isr);
			String line = "";
			String[] sites = null;
			while ((line = br.readLine()) != null) {
				sites = line.split(" ");
				if (sites.length < 2)
				{
					System.err.println("数据构造错误: " + line);
				}
				Edge e = new Edge();
				e.setEdge(sites[0], sites[1], transfer, head);
			}
		} catch (IOException e) {
			System.out.println("map文件读入异常");
			return false;
		} finally {
			try {
				br.close();
				isr.close();
				fis.close();
			} catch (IOException e) {
				System.out.println("map文件关闭异常");
				return false;
			}
		}
		return true;
	}
	/**
	 * @brief: init transfer
	 * @return: true  boolean successful
	 *          false boolean fail
	 */
	public static boolean initTransfer() {
		for (int i = 1; i <= 8; i++) {
			String trans = "X" + i;
			transfer.add(trans);
		}
		return true;
	}
	
	/**
	 * @brief: 测试方法
	 */
	
	public static void test() {
		// test adj
		/**
		for (String key: head.keySet()) {
			System.out.println("key = " + key);
			System.out.println("size = " + head.get(key).size());
			Vector<Edge> adj = head.get(key);
			for (Edge e: adj) {
				System.out.println("from = " + e.getFrom());
				System.out.println("to = " + e.getTo());
				System.out.println("val = " + e.getDis());
			}
		}
		*/
		int ans = SPFA("L2-8", "L2-2");
		System.out.println("ans = " + ans);
		
	}
	
	public static void main(String[] args) {
		if (!initTransfer() || !getStation() || !buildEdges()) {
			System.err.println("构建图出现错误，请检查map");
		} else {
			//test()
			File in_file = new File(IN_FILE);
			FileInputStream fis = null;
			InputStreamReader isr = null;
			BufferedReader br = null;
			try {
				fis = new FileInputStream(in_file);
				isr = new InputStreamReader(fis, "UTF-8");
				br = new BufferedReader(isr);
				String line = "";
				String[] sites = null;
				while ((line = br.readLine()) != null) {
					sites = line.split(",");
					if (sites.length < 2)
					{
						System.out.println(line + ": 数据输入格式出错");
					}
					String start = sites[0];
					String end = sites[1];
					int ans = SPFA(start, end);
					if (ans != -1) {
						double pay = distances.get(end) <= 5 ? 2 : 2 + ((distances.get(end) - 5) * 0.5);
						// 控制4.0这样的输出
						if (pay == (int)pay) {
							System.out.print(start + "," + end + "=" + (int)pay + ":");
						} else {
							System.out.print(start + "," + end + "=" + pay + ":");
						}
						String s = end;
						/**由于是逆序的，需要用堆栈来正序输出*/
						Stack<String> routeStack = new Stack<String>();
						while (route.containsKey(s) && !s.equals(start)) {
							routeStack.push(s);
							s = route.get(s);
						}
						routeStack.push(start);
						int format = 0;
						while (!routeStack.empty()) {
							if (format == 0) {
								System.out.print(routeStack.pop());
							} else {
								System.out.print("," + routeStack.pop());
							}
							format++;
						}
						System.out.println();
					}
				}
			} catch (IOException e) {
				System.out.println("输入数据文件读入异常");
			} finally {
				try {
					br.close();
					isr.close();
					fis.close();
				} catch (IOException e) {
					System.out.println("输入数据文件关闭异常");
				}
			}
		}
		
	}
}
