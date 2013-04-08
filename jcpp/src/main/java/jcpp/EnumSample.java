package jcpp;

public enum EnumSample{
	E1("E1"),
	E2("E2"),
	E3("E3"),
	E4("E4"),
	E5("E5");
	private String fieldString;

	EnumSample(String fieldString){
		this.fieldString=fieldString;
	}

	public String getFieldString(){
		return fieldString;
	}
}