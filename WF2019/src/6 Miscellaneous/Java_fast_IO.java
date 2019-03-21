public class javatemplate {
	public static void main(String[] args){
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Task solver = new Task();
		solver.solve(1, in, out);
		out.close();
	}
	
	static class Task{
		public void solve(int testNumber, InputReader in, PrintWriter out){
			BigInteger b1 = in.nextBigInteger();
			int x = in.nextInt();
			BigInteger b2 = BigInteger.valueOf(x);
			out.println(b1.add(b2));
			out.println(b1.subtract(b2));
			out.println(b1.multiply(b2));
			out.println(b1.divide(b2));
			out.println(b1.gcd(b2));
			BigDecimal b3 = in.nextBigDecimal();
			double d = in.nextDouble();
			BigDecimal b4 = BigDecimal.valueOf(d);
			out.println(b3.add(b4));
			out.println(b3.subtract(b4));
			out.println(b3.multiply(b4));
			out.println(b3.divide(b4, 10, BigDecimal.ROUND_HALF_UP));
			b3 = b3.setScale(100, BigDecimal.ROUND_UP);
			out.println(b3);
			Vector <Integer> vec = new Vector <>();
			Collections.sort(vec);
		}
	}
	
	static class InputReader{
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		
		public InputReader(InputStream stream){
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null;
		}
		
		public String next(){
			while (null == tokenizer || !tokenizer.hasMoreTokens()){
				try{
					tokenizer = new StringTokenizer(reader.readLine());
				}
				catch (IOException e){
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}
		
		public int nextInt(){
			return Integer.parseInt(next());
		}
		
		public double nextDouble(){
			return Double.parseDouble(next());
		}
		
		public BigInteger nextBigInteger(){
			return new BigInteger(next());
		}
		
		public BigDecimal nextBigDecimal(){
			return new BigDecimal(next());
		}
	}
}
