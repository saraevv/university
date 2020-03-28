package com.saraew;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.labels.PieSectionLabelGenerator;
import org.jfree.chart.labels.StandardPieSectionLabelGenerator;
import org.jfree.chart.plot.PiePlot;
import org.jfree.data.general.DefaultPieDataset;

import javax.swing.*;
import java.text.DecimalFormat;
import java.util.ArrayList;

public class ThirdTask extends JPanel {
    private DefaultPieDataset pieDataset;
    ChartPanel panel;

    public ThirdTask() {
        pieDataset = new DefaultPieDataset();
        panel = new ChartPanel(ChartFactory.createPieChart("Chart", pieDataset, true, true, false));
        this.add(panel);
    }

    public void setDataList(ArrayList<Data> dataList) {
        pieDataset.clear();
        for (Data data : dataList) {
            pieDataset.setValue(data.getName(), data.getValue());
        }
        JFreeChart chart = ChartFactory.createPieChart("Chart", pieDataset, true, true, false);
        PieSectionLabelGenerator generator = new StandardPieSectionLabelGenerator("{0}: {1} ({2})",
                new DecimalFormat("0"), new DecimalFormat("0%"));
        PiePlot plot = (PiePlot) chart.getPlot();
        plot.setLabelGenerator(generator);
        panel = new ChartPanel(chart);
    }
}
