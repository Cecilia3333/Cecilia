package com.example.dialog;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {
	private TextView myTV;
	private Button myBtn;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		//根据Id获取组件
		myTV=(TextView)findViewById(R.id.TextView01);
		myBtn=(Button)findViewById(R.id.Button01);
		//获得Builder对象
		final AlertDialog.Builder builder=new AlertDialog.Builder(this);
		//在按钮上注册监听器
		myBtn.setOnClickListener(new OnClickListener(){
			public void onClick(View v){
				//通过builder对象设置对话框信息
				builder.setMessage("真的要删除该记录吗？")
				//设置确定按钮及其相应事件处理
				.setPositiveButton("是", new DialogInterface.OnClickListener(){
					public void onClick(DialogInterface dialog,int which){
						myTV.setText("删除成功！");}})
						//设置取消按钮及其相应事件处理
				.setNegativeButton("否", new DialogInterface.OnClickListener(){
					public void onClick(DialogInterface dialog,int which){
						myTV.setText("取消删除！");}});
				//创建对话框
				AlertDialog ad=builder.create();
				//显示对话框
				ad.show();
					}
				});
			}
		}
