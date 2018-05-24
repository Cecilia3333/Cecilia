package com.example.button;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
public class MainActivity extends Activity {
	Button btnYellow,btnBlue;
	@Override
	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		btnYellow=(Button)this.findViewById(R.id.btnYellow);
		btnBlue=(Button)this.findViewById(R.id.btnBlue);
		btnYellow.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v){
				getWindow().setBackgroundDrawableResource(R.color.yellow);
			}
		});
		btnBlue.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v){
				getWindow().setBackgroundDrawableResource(R.color.blue);
			}
		});
	}
}

