package com.openlab;
//ORM   
public class Employee {
	int   eno;
    String  ename;
    String  job;
    double  salary;
    int   age;
	public Employee(int eno, String ename, String job, double salary, int age) {
		super();
		this.eno = eno;
		this.ename = ename;
		this.job = job;
		this.salary = salary;
		this.age = age;
	}
	public int getEno() {
		return eno;
	}
	public void setEno(int eno) {
		this.eno = eno;
	}
	public String getEname() {
		return ename;
	}
	public void setEname(String ename) {
		this.ename = ename;
	}
	public String getJob() {
		return job;
	}
	public void setJob(String job) {
		this.job = job;
	}
	public double getSalary() {
		return salary;
	}
	public void setSalary(double salary) {
		this.salary = salary;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
    public String toString(){
    	return  this.eno+" "+ this.ename+" "+this.job+" "+this.salary+" "+this.age;
    }
    
}
